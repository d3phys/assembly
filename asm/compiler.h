#ifndef COMPILER_H_
#define COMPILER_H_

#include <stdio.h>
#include "parse.h"

struct code_t {
        token_t *cmds = nullptr;
        size_t n_cmds = 0;
};

struct header_t {
        unsigned int signature = 0x4441444;
        unsigned int version = 1;
        size_t n_cmds = 0;
};

struct asm_compiler_t {
        header_t header;
        code_t asm_code = {0};
        char  *bytecode = {0};
};

int preprocess_asm(code_t *asm_code, FILE *const out);
int compile_asm(code_t *asm_code, char *const bytecode);
int decompile_asm(char *bytecode);

int construct_asm_code(code_t *const asm_code, char *const assembly);
void destruct_asm_code(code_t *const asm_code);


#endif /* COMPILER_H_ */
