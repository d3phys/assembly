#ifndef CPU_H_
#define CPU_H_

#include <thrw.h>
#include <assembly.h>
#include "../assembler/compiler.h"
#include "stack/stack.h"

struct cpu_t {
        int rax = 0;
        int rbx = 0;
        int rcx = 0;
        int rdx = 0;
        stack_t stack = {0};
};

typedef uint32_t cmd_t;
typedef uint16_t opcode_t;
typedef double   arg_t;

const cmd_t OPCODE_MASK = 0x011111111;

int construct_cpu(cpu_t *const cpu);
int execute(cpu_t *const cpu, const char *const bytecode);


// 010011000011001101101010111101111111011101010101
#endif /* CPU_H_ */
