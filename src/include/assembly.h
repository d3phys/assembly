#ifndef ASSEMBLY_H_
#define ASSEMBLY_H_

#include "hash.h"

const char DLM_COMMENTS[] = ";";
const char DLM_TOKS[]     = " \t";
const char DLM_CMDS[]     = "\n";
/*
#define NAMEONIC(NAME)                                                \
        const int  HASH##NAME = murmur_hash(#NAME, sizeof(#NAME), 0); \
        const char M_##NAME[] = #NAME;                                \
        const int  OPCODE_##NAME = #NAME;                           \

MNEMONIC(PUSH)
MNEMONIC(POP)
MNEMONIC(SUB)
MNEMONIC(MUL)
*/

#endif /* ASSEMBLY_H_ */
