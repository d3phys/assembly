#include <stdio.h>
#include "cpu.h"

int construct_cpu(cpu_t *const cpu)
{
        int err = 0;
        construct_stack(&cpu->stack, &err);

        return err;
}

int execute(cpu_t *const cpu, const char *const bytecode)
{
        header_t hdr = *(const header_t *)bytecode;
        const char *bc = bytecode + sizeof(header_t);

        cmd_t cmd = 0;
        arg_t arg = 0;
        opcode_t opcode = 0;
        for (size_t i = 0; i < hdr.n_cmds; i++) {
                cmd = *(const cmd_t *)bc;
                opcode = (opcode_t)cmd;

                switch (opcode) {
/*
                case CMD_PUSH:
                        break;
                case CMD_POP:
                        break;
                case CMD_ADD:
                        break;
                case CMD_SUB:
                        break;
                        */
                default:
                        break;

                }
        }
        
        return 0;
}

