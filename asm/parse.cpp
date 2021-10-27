#include <assert.h>
#include <string.h>

#include "parse.h"

size_t extract_tokens(char *const buf, token_t *tokens, 
                      const char *const delim, size_t n_tokens) 
{
        assert(buf);
        assert(delim);
        assert(tokens);

        size_t n_wds = 0;

        char *tok = strtok(buf, delim);
        while (tok && n_tokens-- > 0) {
                *tokens++ = tok;
                n_wds++;
                tok = strtok(nullptr, delim);
        }

        return n_wds;
}

size_t occurs(const char ch, const char *const str) 
{
        assert(str);

        const char *pos = str;
        size_t n_ch = 0;
        while (*pos != '\0')
                if (*pos++ == '\n')
                        n_ch++;
        return n_ch;
}


