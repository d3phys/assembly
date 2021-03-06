#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include <assembly.h>
#include <thrw.h>
#include <hash.h>

#include "parse.h"
#include "compiler.h"

const size_t N_LABELS = 64;

struct label_t {
        uint32_t hash = 0x00;
        arg_t address = 0x00;
};

struct labels_t {
        label_t labels[N_LABELS] = {0};
        size_t count = 0;
};

static inline void uncomment(char *const cmd)
{
        assert(cmd);

        char *comment = strchr(cmd, ';');
        if (comment)
                *comment = '\0';
}

static char *find(char *const str, const char ch)
{
        assert(str);

        char *c = str;
        while (*c != ch && *c != '\0')
                c++;

        return c; 
}

static char *skip(char *const str, const char ch)
{
        assert(str);

        char *c = str;
        while (*c == ch && *c != '\0')
                c++;

        return c; 
}

#define PUSH_ARG(arg, arg_start, out)                               \
        do {                                                        \
                if (arg_start != arg) {                             \
                        *(arg) = '\0';                              \
                        fprintf(out, "%s %s\n", MN_PUSH, arg_start); \
                }                                                   \
                arg_start = arg + 1;                                \
        } while(0)


int preprocess_asm(code_t *code, FILE *const out) 
{
        assert(code);
        assert(out);

        int error = 0;
        char args[64] = {0};
        char *mem = nullptr;
        char *arg = args;
        char *arg_start = arg;
        for (size_t i = 0; i < code->n_cmds; i++) {

                uncomment(code->cmds[i]);

                code->cmds[i] = skip(code->cmds[i], ' ');
                if (*code->cmds[i] == '\0')
                        continue;

                arg = find(code->cmds[i], ' ');
                if (*arg != '\0')
                        *arg++ = '\0';

                mem = find(arg, '[');
                if (*mem != '\0') {
                        arg = find(mem, ']');
                        thrw(goto segfault, *arg == '\0',
                             "Can't find close bracket ]. Line: %lu\n", i + 1);

                        *arg = '\0';
                        arg = mem + 1;
                }

                error = reverse_notation(arg, args);
                thrw(goto segfault, error, "Syntax error at not empty line %lu\n", i + 1);

                if (*args == '\0') {
                        fprintf(out, "%s\n", code->cmds[i]);
                        continue;
                }

                arg = args;
                arg_start = arg;

                while (*arg != '\0') {
                        switch (*arg) {
                        case ' ':
                                PUSH_ARG(arg, arg_start, out);
                                break;

                        case '-':
                                PUSH_ARG(arg, arg_start, out);
                                fprintf(out, "%s\n", MN_SUB);
                                break;

                        case '+':
                                PUSH_ARG(arg, arg_start, out);
                                fprintf(out, "%s\n", MN_ADD);
                                break;

                        case '*':
                                PUSH_ARG(arg, arg_start, out);
                                fprintf(out, "%s\n", MN_MUL);
                                break;

                        case '/':
                                PUSH_ARG(arg, arg_start, out);
                                fprintf(out, "%s\n", MN_DIV);
                                break;

                        case '^':
                                PUSH_ARG(arg, arg_start, out);
                                fprintf(out, "%s\n", MN_POW);
                                break;
                        default:
                                break;
                        }

                        arg++;
                }

                if (arg_start != args) 
                        if (*mem != '\0')
                                fprintf(out, "%s %s\n%s [%s]\n", 
                                        MN_POP, MN_TX, code->cmds[i], MN_TX); 
                        else
                                fprintf(out, "%s %s\n%s %s\n", 
                                        MN_POP, MN_TX, code->cmds[i], MN_TX); 
                else
                        if (*mem != '\0')
                                fprintf(out, "%s [%s]\n", code->cmds[i], args);
                        else
                                fprintf(out, "%s %s\n", code->cmds[i], args);
        }

        return 0;

segfault:
        printf("%d", *mem);
        return -1;
}

#undef PUSH_ARG

#define CMD(name, opcode, mnemonic, hash) \
        case hash:                        \
                return name;

static cmd_t get_cmd(uint32_t hash)
{
        switch (hash) {
#include <commands>

        default:
                fprintf(stderr, "Invalid command with hash 0x%x\n", hash);
                return 0xFF;
        }
}

#undef CMD


#define REG(name, num, mnemonic, hash)       \
        case hash:                           \
                return name;

static arg_t get_arg(char *cmd, cmd_t *const bit_mask, const labels_t *const lb)
{
        assert(cmd);
        assert(bit_mask);
        assert(lb);

        arg_t arg = 0;
        char *mem = find(cmd, '[');
        if (*mem != '\0') {
                *bit_mask |= MEM_T;

                cmd = ++mem;
                mem = find(mem, ']');
        }

        char *end = cmd;
        arg = strtod(cmd, &end);
        if (end != cmd) {
                *bit_mask |= VAL_T;
                return arg;
        }
        
        assert(mem > cmd);
        uint32_t hash = murmur_hash(cmd, (size_t)(mem - cmd), SEED); 

        *bit_mask |= REG_T;

        switch (hash) {
#include <registers>
        default:
                break;
        }

        *bit_mask &= (cmd_t) ~REG_T;
        *bit_mask |= (cmd_t)  VAL_T;

        for (size_t i = 0; i < lb->count; i++) {
                if (hash == lb->labels[i].hash)
                        return lb->labels[i].address;
        }

        return 0;
}

#undef REG

static int compile(const code_t *const code, char *const bytecode, 
                   labels_t *const lb, size_t *const n_written)
{
        assert(code);
        assert(bytecode);
        assert(n_written);
        assert(lb);

        *n_written = 0;

        uint32_t hash = 0x00;
        char *bc = bytecode;
        char *ip = nullptr;
        cmd_t cmd = 0x00;
        arg_t arg = 0x00;
        cmd_t bit_mask = 0x00;

        for (size_t i = 0; i < code->n_cmds; i++) {
                bit_mask = 0x00;

                ip = find(code->cmds[i], ' ');

                if (*(ip - 1) == ':') {
                        thrw(goto error, (lb->count == N_LABELS), 
                             "Labels amount overflow\n");

                        assert(ip > code->cmds[i]);
                        hash = murmur_hash(code->cmds[i], 
                                           (size_t)(ip - code->cmds[i] - 1), SEED); 

                        for (size_t j = 0; j < lb->count; j++) {
                                if (hash == lb->labels[j].hash) {
                                        assert(bc > bytecode);
                                        lb->labels[j].address = (arg_t)(bc - bytecode);
                                        hash = 0;
                                        break;
                                }
                        }

                        if (hash) {
                                lb->labels[lb->count].hash  = hash;

                                assert(bc > bytecode);
                                lb->labels[lb->count++].address = (arg_t)(bc - bytecode);
                        }

                        continue;
                }

                assert(ip > code->cmds[i]);
                hash = murmur_hash(code->cmds[i], 
                                   (size_t)(ip - code->cmds[i]), SEED); 

                cmd = get_cmd(hash);
                if (cmd == 0xFF)
                        fprintf(stderr, "Compilation error on line: %lu\n", i + 1);

                if (*ip != '\0')
                        arg = get_arg(ip + 1, &bit_mask, lb);

                *(cmd_t *)bc = cmd | bit_mask;
                bc += sizeof(cmd_t);
                *n_written += sizeof(cmd_t);

                if (bit_mask) {
                        *(arg_t *)bc = arg;
                        bc += sizeof(arg_t);
                        *n_written += sizeof(arg_t);
                }
        }

        return 0;

error:
        return -1;
}

int compile_asm(const code_t *const code, 
                char *const bytecode, size_t *const n_written) 
{
        assert(code);
        assert(bytecode);
        assert(n_written);

        labels_t lb = {0};

        char *bc = bytecode;

        header_t hdr = {SIGNATURE,
                        VERSION,
                        PATCHLEVEL};

        *(header_t *)bc = hdr;
        bc += sizeof(header_t);

        compile(code, bc, &lb, n_written);
        compile(code, bc, &lb, n_written);

        *n_written += sizeof(header_t);

        return 0;
}

int construct_asm_code(code_t *const asm_code, char *const buf)
{
        assert(asm_code);
        assert(buf);

        errno = 0;

        size_t n_toks = 0;
        size_t n_cmds = occurs('\n', buf);

        token_t  *cmds = (token_t *)calloc(n_cmds, sizeof(token_t));
        thrw(goto finally, (cmds == nullptr),
             "Can't calloc memory for commands: %s", strerror(errno));

        n_toks = extract_tokens(buf, cmds, "\n", n_cmds);
        if (n_toks < n_cmds) {
                n_cmds = n_toks;
                void *mem = realloc(cmds, sizeof(token_t) * n_cmds);
                thrw(goto finally, (mem == nullptr),
                     "Can't realloc memory for commands: %s", 
                                                     strerror(errno));

                cmds = (token_t *)mem;
        }

        asm_code->  cmds =   cmds;
        asm_code->n_cmds = n_cmds;

finally:
        if (errno)
                free(cmds);

        return errno;
}

void destruct_asm_code(code_t *const asm_code) 
{
        assert(asm_code);

        free(asm_code->cmds);
        asm_code->n_cmds = 0;
}


