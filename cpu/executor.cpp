#include <stdio.h>
#include <assembly.h>

#include "executor.h"

int construct_cpu(cpu_t *const cpu)
{
        int err = 0x00;
        construct_stack(&cpu->stack, &err);

        return err;
}

int destruct_cpu(cpu_t *const cpu)
{
        destruct_stack(&cpu->stack);

        return 0;
}

#define ACTION(code, action) \
        case code:           \
                printf("CMD %lx\n", cmd); \
                action       \
                dump_stack(stack);\
                break;

int execute(cpu_t *const cpu, const char *const bytecode)
{
        header_t hdr = *(const header_t *)bytecode;

        cmd_t  cmd = 0x0000;

        arg_t   *const reg   =  cpu->registers;
        arg_t   *const ram   =  cpu->ram;
        stack_t *const stack = &cpu->stack;
        
        char o = 0;
#define ip   cpu->ip
#define temp cpu->temp

        ip = bytecode + sizeof(header_t);

        while (1) {
                cmd = *(const cmd_t *)ip;

                ip += sizeof(cmd_t);

                switch (cmd) {
#include <actions>
                default:
                        break;
                }

        }

#undef ip
#undef temp
        
hlt:
        printf("Here %d\n", __LINE__);
        return 0;
}

