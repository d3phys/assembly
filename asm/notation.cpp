#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>

#include <thrw.h>

#include "parse.h"

static const unsigned int STK_SIZE = 64;

struct stack_t {
        char items[STK_SIZE] = {0};
        unsigned int size = 0;
};

static inline void push(stack_t *const stk, const char item) 
{
        stk->items[++stk->size] = item;
}

static inline char pop(stack_t *const stk) 
{
        return stk->items[stk->size--];
}

static inline char check(stack_t *const stk) 
{
        if (stk->size <= 0)
                return -1;

        return stk->items[stk->size];
}

static int priority(const char op)
{
        switch (op) {
        case '^':
                return 4;

        case '*':
        case '/':
                return 2;

        case '-':
        case '+':
                return 1;

        case ']':
        case ')':
        case '(':
        case '[':
                return 0;

        default:
                return -1;
        }
}

int reverse_notation(const char *infix, char *postfix)
{
        assert(infix);
        assert(postfix);

        static stack_t stk = {0};

        while (*infix != '\0') {

                switch (*infix) {

                case ' ' :
                case '\t':
                        break;

                case '[':
                case '(':
                        *postfix++ = ' ';
                        thrw(goto error, (stk.size >= STK_SIZE), 
                             "Reverse notation stack is full\n");

                        push(&stk, *infix);
                        break;

                case ']':
                        while (check(&stk) != '[') {
                                thrw(goto error, (stk.size <= 1),
                                     "Can't find open bracket ]\n");

                                *postfix++ = pop(&stk);
                        }

                        pop(&stk);
                        break;

                case ')':
                        while (check(&stk) != '(') {
                                thrw(goto error, (stk.size <= 1),
                                     "Can't find open bracket (\n");

                                *postfix++ = pop(&stk);
                        }

                        pop(&stk);
                        break;

                case '^':
                case '*':
                case '/':
                case '-':
                case '+':
                        while (stk.size > 0 && 
                               priority(*infix) <= priority(check(&stk))) 
                        {
                                *postfix++ = pop(&stk);
                        }

                        *postfix++ = ' ';

                        thrw(goto error, (stk.size >= STK_SIZE), 
                             "Reverse notation stack is full\n");

                        push(&stk, *infix);

                        break;

                default:
                        *postfix++ = *infix;
                        break;
                }

                infix++;
        }

        while (stk.size > 0)
                *postfix++ = pop(&stk);

        *postfix = '\0';
        stk.size = 0;
        return 0;

error:
        return -1;
}


