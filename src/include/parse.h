/**
 * @file
 * @brief Assembly asm_code parser
 * @author d3phys
 * @date 08.10.2021
 */

#ifndef PARSE_H_
#define PARSE_H_

#include <sys/mman.h>

const size_t CMD_TOKENS = 0x0004;

struct token_t {
        char *start = nullptr;
        size_t len  = 0;
};

struct command_t {
        token_t tokens[CMD_TOKENS] = {0};
        size_t n_tokens = 0;
};

struct asm_code_t {
        token_t *cmds = nullptr;
        size_t n_cmds = 0;
};

size_t extract_tokens(char *const buf, token_t *tokens, 
                      const char *const delim, size_t n_tokens);

int construct_asm_code(asm_code_t *const asm_code, char *const buf);
int destruct_asm_code (asm_code_t *const asm_code);

int save(const char *const file,
         const char *const buf, size_t n_bytes);

/**
 * @brief Reads file to a buffer
 */
int bufferise(const char *const file, 
              char **const buf, size_t *const size = nullptr);

#endif /* PARSE_H_ */


