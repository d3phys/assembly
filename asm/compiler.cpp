#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assembly.h>

#include "parse.h"
#include "compiler.h"
#include <thrw.h>
#include <hash.h>

static inline void uncomment(char *const cmd)
{
        assert(cmd);
        char *comment = strchr(cmd, ';');
        if (comment)
                *comment = '\0';
}

static char *find(char *const str, const char ch)
{
        char *c = str;
        while (*c != ch && *c != '\0')
                c++;

        return c; 
}

static char *skip(char *const str, const char ch)
{
        char *c = str;
        while (*c == ch && *c != '\0')
                c++;

        return c; 
}

#define PUSH_ARG(arg, arg_start, out)                               \
        do {                                                        \
                if (arg_start != arg) {                             \
                        *(arg) = '\0';                              \
                        fprintf(out, "%s %s\n", MN_PSH, arg_start); \
                }                                                   \
                arg_start = arg + 1;                                \
        } while(0)


int preprocess_asm(code_t *code, FILE *const out) 
{
        for (int i = 0; i < code->n_cmds; i++) {
                if (*code->cmds[i] != '\0')
                        printf("%s\n", code->cmds[i]);
        }

        char args[64] = {0};
        char *mem = nullptr;
        char *arg = args;
        char *arg_start = arg;
        for (size_t i = 0; i < code->n_cmds; i++) {

                uncomment(code->cmds[i]);

                code->cmds[i] = skip(code->cmds[i], ' ');

                arg = find(code->cmds[i], ' ');
                if (*arg != '\0')
                        *arg++ = '\0';

                mem = find(arg, '[');

                reverse_notation(arg, args);

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
}

#undef PUSH_ARG

/*
#define CMD(name, opcode, mnemonic, hash)    \
        const opcode_t name = opcode;        \
        const char MN_##name[]   = mnemonic; \
        const uint32_t HASH_##name   = hash; \

#include <commands>

#define CMD(name, opcode, mnemonic, hash)    \
        case HASH_##name:                       \
                fprintf                                \
                break;
#undef CMD

#define REG(name, num, mnemonic, hash)       \
        const int name = num;                \
        const char MN_##name[] = mnemonic; \
        const uint32_t HASH_##name = hash; \

#include <registers>

#undef REG 

#define CMD
*/

#define CMD(name, opcode, mnemonic, hash) \
        case hash:                        \
                return name;

static cmd_t get_cmd(uint32_t hash)
{
        switch (hash) {
#include <commands>

        default:
                assert(0);
                return 0;
        }
}

#undef CMD


#define REG(name, num, mnemonic, hash)       \
        case hash:                           \
                return name;

static int get_arg(char *cmd, cmd_t *const bit_mask)
{
        arg_t arg = 0;
        char *mem = find(cmd, '[');
        if (*mem != '\0') {
                *bit_mask |= MEM_T;

                cmd = ++mem;

                mem = find(mem, ']');
                *mem = '\0';
        }

        char *end = cmd;
        arg = (arg_t)strtod(cmd, &end);
        if (end != cmd) {
                *bit_mask |= VAL_T;
                return arg;
        }
        
        *bit_mask |= REG_T;
        uint32_t hash = murmur_hash(cmd, mem - cmd, SEED); 

        switch (hash) {
#include <registers>

        default:
                assert(0);
                break;
        }

        return 0;
}

#undef REG

int compile_asm(code_t *code, char *const bytecode) 
{
        assert(code);
        assert(bytecode);

        uint32_t hash = 0x00;
        char *bc = bytecode;
        size_t n_bytes = 0;
        char *ip = nullptr;
        cmd_t cmd = 0x00;
        arg_t arg = 0x00;
        cmd_t bit_mask = 0x00;

        for (size_t i = 0; i < code->n_cmds; i++) {
                ip = find(code->cmds[i], ' ');

                hash = murmur_hash(code->cmds[i], 
                                   ip - code->cmds[i], SEED); 

                cmd = get_cmd(hash);

                if (*ip != '\0')
                        arg = get_arg(ip, &bit_mask);

                *(cmd_t *)bc++ = arg;
                if (bit_mask)
                        *(arg_t *)bc++ = arg;
        }

        return 0;
}

int decompile_asm(char *bytecode);

int construct_asm_code(code_t *const asm_code, char *const buf)
{
        assert(asm_code);
        assert(buf);

        errno = 0;

        size_t n_toks = 0;
        size_t n_cmds = occurs('\n', buf);

        token_t  *cmds = (token_t *)calloc(n_cmds, sizeof(token_t));
        thrw(finally, (cmds == nullptr),
             "Can't calloc memory for commands: %s", strerror(errno));

        n_toks = extract_tokens(buf, cmds, "\n", n_cmds);
        if (n_toks < n_cmds) {
                n_cmds = n_toks;
                void *mem = realloc(cmds, sizeof(token_t) * n_cmds);
                thrw(finally, (mem == nullptr),
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
        free(asm_code->cmds);
        asm_code->n_cmds = 0;
}
