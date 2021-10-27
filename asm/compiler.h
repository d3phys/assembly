#ifndef COMPILER_H_
#define COMPILER_H_

#include <stdio.h>
#include "parse.h"

struct code_t {
        token_t *cmds = nullptr;
        size_t n_cmds = 0;
};

int preprocess_asm(code_t *asm_code, FILE *const out);

int compile_asm(const code_t *const code, 
                char *const bytecode, size_t *const n_written);

int decompile_asm(char *bytecode);

int construct_asm_code(code_t *const asm_code, char *const assembly);
void destruct_asm_code(code_t *const asm_code);


#endif /* COMPILER_H_ */
