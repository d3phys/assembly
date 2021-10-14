#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include "include/parse.h"
#include "include/thrw.h"


static off_t get_size(const char *const file);
static size_t occurs(const char ch, const char *const buffer);
static inline int among(const char ch, const char *str);

static char *strtik(char *str, const char *const delim, 
                               size_t *const length = nullptr);

size_t extract_tokens(char *const buf, token_t *tokens, 
                     const char *const delim, size_t n_tokens) 
{
        assert(buf);
        assert(delim);
        assert(tokens);

        size_t n_wds = 0;
        size_t len   = 0;

        char *tok = strtik(buf, delim, &len);
        while (tok && n_tokens-- > 0) {
                tokens->start = tok;
                tokens->len   = len;
                tokens++;
                n_wds++;
                tok = strtik(nullptr, delim, &len);
        }

        return n_wds;
}

int construct_asm_code(asm_code_t *const asm_code, char *const buf)
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

int save(const char *const file,
         const char *const buf, size_t n_bytes)
{
        assert(file);
        assert(buf);

        errno = 0;

        mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
        size_t n_written = 0;
        int fd = -1;

        fd = creat(file, mode);
        thrw(finally, (fd < 0), 
            "Can't open the file %s: %s", file, strerror(errno));

        n_written = write(fd, buf, n_bytes);
        thrw(finally, (n_written != n_bytes),
             "Error while writing. Buffer length: %ld, bytes written: %ld", 
                                                       n_bytes, n_written);

finally:
        if (fd > 0)
                close(fd);

        return errno;
}

int bufferise(const char *const file, 
              char **const buf, size_t *const size)
{
        assert(file);
        errno = 0;

        const int prot = PROT_READ | PROT_WRITE;
        char *bf = nullptr;
        int fd = -1;
        
        off_t fsz = get_size(file);
        thrw(finally, (fsz == -1), 
            "Can't get the file size %s\n", strerror(errno));

        fd = open(file, O_RDONLY); 
        thrw(finally, (fd < 0), 
            "Can't open the file %s: %s\n", file, strerror(errno));

        bf = (char *)mmap(nullptr, fsz + 1, prot, MAP_PRIVATE, fd, 0);
        thrw(finally, (buf == MAP_FAILED), 
            "Can't map the file %s: %s\n",  file, strerror(errno));
        

        if (size)
                *size = fsz + 1;

        bf[fsz] = '\0';
        *buf = bf;

finally:
        if (fd > 0)
                close(fd);

        return errno;
}

static off_t get_size(const char *const file) 
{
        assert(file);
        errno = 0;

        struct stat buf = {};
        int err = stat(file, &buf);
        if (err)
                return -1;

        return buf.st_size;
}

static size_t occurs(const char ch, const char *const str) 
{
        assert(str);

        const char *pos = str;
        size_t n_ch = 0;
        while (*pos != '\0')
                if (*pos++ == '\n')
                        n_ch++;
        return n_ch;
}

static inline int among(const char ch, const char *str)
{
        assert(str);
        while (*str != '\0')
                if (ch == *str++)
                        return 1;

        return 0;
}

#define skip(tok, condition)                            \
        do {                                            \
                while (condition) {                     \
                        if (*(++tok) == '\0') {         \
                                tok = nullptr;          \
                                break;                  \
                        }                               \
                }                                       \
                                                        \
        } while (0)

/*
 * @brief Finds the next token in a null-terminated byte string 
 *                                                      pointed to by str
 *
 * This is a complete analogue of the standard ANSI function strtok().
 * But you can pass an additional parameter 
 * to which the length of the token will be written.
 * This function is designed to be called multiple times 
 * to obtain successive tokens from the same string.
 */
static char *strtik(char *str, const char *const delim, size_t *const len)
{
        assert(delim);

        static char *tok = nullptr;
        if (str)
                tok = str;

        char *start = nullptr;

        if (tok) {
                skip(tok, among(*tok, delim));
                if (tok == nullptr)
                        return start;

                start = tok;

                skip(tok, !among(*tok, delim));
                if (tok == nullptr) {
                        if (len)
                                *len = strlen(start);
                        return start;
                }
                
                if (len)
                        *len = tok - start;

                *tok++ = '\0';
        }

        return start;
}

#undef skip


