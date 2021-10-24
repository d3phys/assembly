#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "compiler.h"
#include "parse.h"

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

#define PUSH_ARG(arg, arg_start)                        \
        do {                                            \
                if (arg_start != arg) {                 \
                        *(arg) = '\0';                  \
                        printf("push %s\n", arg_start); \
                }                                       \
                arg_start = arg + 1;                    \
        } while(0)

int main(int argc, char *argv[])
{
        code_t code = {0};
        size_t size = 0;
        char *buf = nullptr;

        bufferise("code", &buf, &size);

        construct_asm_code(&code, buf);
        printf("N: %ld\n", code.n_cmds);

        for (int i = 0; i < code.n_cmds; i++) {
                if (*code.cmds[i] != '\0')
                        printf("%s\n", code.cmds[i]);
        }

        char *arg = nullptr;
        char args[64] = {0};
        for (size_t i = 0; i < code.n_cmds; i++) {

                uncomment(code.cmds[i]);

                code.cmds[i] = skip(code.cmds[i], ' ');

                arg = find(code.cmds[i], ' ');
                if (*arg != '\0')
                        *arg++ = '\0';

                reverse_notation(arg, args);

                char *arg = args;
                char *arg_start = arg;

                while (*arg != '\0') {
                        switch (*arg) {
                        case ' ':
                                PUSH_ARG(arg, arg_start);
                                break;

                        case '-':
                                PUSH_ARG(arg, arg_start);
                                printf("sub\n");
                                break;

                        case '+':
                                PUSH_ARG(arg, arg_start);
                                printf("add\n");
                                break;

                        case '*':
                                PUSH_ARG(arg, arg_start);
                                printf("mul\n");
                                break;

                        case '/':
                                PUSH_ARG(arg, arg_start);
                                printf("div\n");
                                break;
                        default:
                                break;
                        }

                        arg++;
                }

                if (arg_start != args)
                        printf("pop tx\n%s tx\n", code.cmds[i]);
                else
                        printf("%s %s\n", code.cmds[i], args);
        }

        munmap(buf, size);
        destruct_asm_code(&code);
        return 0;
}
