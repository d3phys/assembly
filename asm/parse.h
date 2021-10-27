/**
 * @file
 * @brief Parser utils
 * @author d3phys
 * @date 27.10.2021
 */

#ifndef PARSE_H_
#define PARSE_H_

#include <stddef.h>

typedef char * token_t;

int reverse_notation(const char *infix, char *postfix);

size_t extract_tokens(char *const buf, token_t *tokens, 
                      const char *const delim, size_t n_tokens);

size_t occurs(const char ch, const char *const buffer);


#endif /* PARSE_H_ */
