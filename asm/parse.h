/**
 * @file
 * @brief Parser utils
 * @author d3phys
 * @date 15.10.2021
 */

#ifndef PARSE_H_
#define PARSE_H_

#include <sys/mman.h>

typedef char * token_t;

int reverse_notation(const char *infix, char *postfix);

size_t extract_tokens(char *const buf, token_t *tokens, 
                      const char *const delim, size_t n_tokens);

size_t occurs(const char ch, const char *const buffer);
off_t get_size(const char *const file);
char *strtik(char *str, const char *const delim, size_t *const len = nullptr);

int save(const char *const file,
         const char *const buf, size_t n_bytes);

int fmap(const char *const file, char **const buf, size_t *const size);

#endif /* PARSE_H_ */


