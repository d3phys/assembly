#include "parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>

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
        case '(':
                return 16;

        case '^':
                return 4;

        case '*':
        case '/':
                return 2;

        case '-':
        case '+':
                return 1;

        case ')':
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

                case '(':
                case ')':
                case '^':
                case '*':
                case '/':
                case '-':
                case '+':
                        while (check(&stk) != '(' && 
                               priority(*infix) <= priority(check(&stk))) 
                        {
                                *postfix++ = pop(&stk);
                                if (stk.size == 0)
                                        break;
                        }

                        if (*infix == ')') {
                                pop(&stk);
                                break;
                        }

                        if (*infix != '(')
                                *postfix++ = ' ';

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
}

/*
esip = sip;
arg = strtod(sip, &esip);
if (esip != sip)
        printf("push %lf\n", arg);
else {
*/
/*
int main()
{
        // char x[] = "ax - cd           (bx- cx * (ax-  0x001)) *   - 3 * dx   ^ 2  + 32 ^ 3";
        char x[] = "(dx- 0x032) / 0x02 +ax * (32 - 21)  - cx";

        //char x[] = "0x0032 + 32";
        char d[100] = {0};
        int err = reverse_notation(x, d);
        printf("ERROR: %d\n", err);
        printf("%s\n", x);
        printf("%s\n", d);

        printf("arr: %p\n", d);
        char *p = d;
        printf("end: %p\n", p);
        double a = strtod(d, &p);
        printf("end: %p\n", p);
        printf("endch: %c\n", *p);
        if (p == d)
                printf("Error \n");

        printf("num: %lf\nerrno: %d\n", a, errno);


        double arg = 0;
        int no = 0;
        char *sip = d;
        char *ip = d;
        char *esip = sip;

        while (*ip != '\0') {
                //printf("%c\n", *ip);
                switch (*ip) {
                case ' ':
                        if (sip != ip) {
                                esip = sip;
                                arg = strtod(sip, &esip);
                                if (esip != sip)
                                        printf("push %lf\n", arg);
                                else {
                                        *(ip-1) = '\0';
                                        printf("push %s\n", sip);
                                }
                        }
                        sip = ip + 1;
                        break;

                case '-':
                        if (sip != ip) {
                                esip = sip;
                                arg = strtod(sip, &esip);
                                if (esip != sip)
                                        printf("push %lf\n", arg);
                                else {
                                        *(ip-1) = '\0';
                                        printf("push %s\n", sip);
                                }
                        }
                        sip = ip + 1;
                        printf("sub\n");
                        break;

                case '+':
                        if (sip != ip) {
                                esip = sip;
                                arg = strtod(sip, &esip);
                                if (esip != sip)
                                        printf("push %lf\n", arg);
                                else {
                                        *(ip-1) = '\0';
                                        printf("push %s\n", sip);
                                }
                        }
                        sip = ip + 1;
                        printf("add\n");
                        break;

                case '*':
                        if (sip != ip) {
                                esip = sip;
                                arg = strtod(sip, &esip);
                                if (esip != sip)
                                        printf("push %lf\n", arg);
                                else {
                                        *(ip-1) = '\0';
                                        printf("push %s\n", sip);
                                }
                        }
                        sip = ip + 1;
                        printf("mul\n");
                        break;

                case '/':
                        if (sip != ip) {
                                esip = sip;
                                arg = strtod(sip, &esip);
                                if (esip != sip)
                                        printf("push %lf\n", arg);
                                else {
                                        *(ip-1) = '\0';
                                        printf("push %s\n", sip);
                                }
                        }
                        sip = ip + 1;
                        printf("div\n");
                        break;
                default:
                        break;
                }

                ip++;
        }

        //printf("%s\n", d);
        printf("Hello from rpn\n");
        return 0;
}

*/
