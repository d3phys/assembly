#ifndef ASSEMBLY_H_
#define ASSEMBLY_H_

#include "hash.h"

const char DLM_COMMENTS[] = ";";
const char DLM_TOKS[]     = " \t";
const char DLM_CMDS[]     = "\n";

#define MNEMONIC(MNEM)                                          \
        const int  MNEM = murmur_hash(#MNEM, sizeof(#MNEM), 0);  \
        const char M_##MNEM[] = #MNEM;\

MNEMONIC(PUSH)
MNEMONIC(POP)
MNEMONIC(SUB)
MNEMONIC(MUL)

#endif /* ASSEMBLY_H_ */
