#include <stdio.h>
#include <assembly.h>

#include "executor.h"

int construct_cpu(cpu_t *const cpu)
{
        int err = 0x00;
        construct_stack(&cpu->stack, &err);

        return err;
}

int execute(cpu_t *const cpu, const char *const bytecode)
{
        header_t hdr = *(const header_t *)bytecode;

        cmd_t  cmd = 0x0000;
        arg_t *arg = nullptr;
        
#define pop        pop_stack (&cpu->stack)
#define push(item) push_stack(&cpu->stack, item)
#define skip       cpu->ip += sizeof(arg_t);

#define RGX(num)   cpu->registers[(uint64_t)num]
#define IP         cpu->ip
#define ARG        *(arg_t *)cpu->ip

        cpu->ip = bytecode + sizeof(header_t);

        while (1) {
                cmd = *(const cmd_t *)cpu->ip;
                cpu->ip += sizeof(cmd_t);

                switch (cmd) {
                        case POP | 0x000:
                                printf("POP 0\n");
                                pop;
                                break;
                        case POP | REG_T:
                                printf("POP REG\n");
                                RGX(ARG) = pop;
                                skip;
                                break;
                        case PSH | REG_T:
                                printf("PUSH REG\n");
                                push(RGX(ARG));
                                skip;
                                break;
                        case SUB:
                                printf("SUB\n");
                                RGX(0) = pop;
                                push(RGX(0) - pop);
                                break;
                        case ADD:
                                printf("ADD\n");
                                push(pop + pop);
                                break;
                        case MUL:
                                printf("MUL\n");
                                push(pop * pop);
                                break;
                }

        }
        
        return 0;
}

