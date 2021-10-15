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

size_t extract_tokens(char *const buf, token_t *tokens, 
                      const char *const delim, size_t n_tokens);

size_t occurs(const char ch, const char *const buffer);
off_t get_size(const char *const file);
char *strtik(char *str, const char *const delim, size_t *const len = nullptr);

int save(const char *const file,
         const char *const buf, size_t n_bytes);

int bufferise(const char *const file, 
              char **const buf, size_t *const size = nullptr);

#endif /* PARSE_H_ */


