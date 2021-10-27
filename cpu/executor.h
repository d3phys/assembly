#ifndef CPU_H_
#define CPU_H_

#include <thrw.h>
#include <assembly.h>

#include "stack.h"

const size_t N_REGS = 0x08;

struct cpu_t {
        arg_t registers[N_REGS] = {0};
        stack_t stack = {0};
        const char *ip = 0;
};


int construct_cpu(cpu_t *const cpu);
int execute(cpu_t *const cpu, const char *const bytecode);


#endif /* CPU_H_ */
