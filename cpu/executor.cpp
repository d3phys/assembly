#include <stdio.h>
#include <string.h>
#include <assembly.h>
#include <math.h>
#include <assert.h>
#include <errno.h>

#include "executor.h"

int construct_cpu(cpu_t *const cpu)
{
        int err = 0x00;
        construct_stack(&cpu->stack, &err);

        cpu->ram = (double *)calloc(sizeof(double), RAM_CAP);
        if (!cpu->ram) {
                err = errno; 
                fprintf(stderr, "Can't create CPU RAM: %s\n", strerror(errno));
        }

        return err;
}

int destruct_cpu(cpu_t *const cpu)
{
        destruct_stack(&cpu->stack);
        free(cpu->ram);

        return 0;
}

#define ACTION(code, action)       \
        case code:                 \
                action             \
                dump_stack(stack); \
                break;

int execute(cpu_t *const cpu, const char *const bytecode)
{
        header_t hdr = *(const header_t *)bytecode;

        cmd_t  cmd = 0x0000;

        arg_t   *const reg   =  cpu->registers;
        arg_t   *const ram   =  cpu->ram;
        stack_t *const stack = &cpu->stack;

#define ip   cpu->ip
#define temp cpu->temp
#define arg  *(const arg_t *)ip 

        const char *const start = bytecode + sizeof(header_t);
        ip = start;

        while (1) {
                cmd = *(const cmd_t *)ip;

                ip += sizeof(cmd_t);

                switch (cmd) {
#include <actions>
#include <jmp>
                default:
                        assert(0);
                        break;
                }

        }

#undef ip
#undef temp
        
hlt:
        printf("Here %d\n", __LINE__);
        return 0;
}

