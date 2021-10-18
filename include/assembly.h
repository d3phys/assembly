#ifndef ASSEMBLY_H_
#define ASSEMBLY_H_

#include "hash.h"

enum commands {
        CMD_PUSH = 0x0001,
        CMD_POP  = 0x0002,
        CMD_ADD  = 0x0003,
        CMD_SUB  = 0x0004,
}

const int32_t SEED = 0xDED64;

const int HASH_PUSH = murmur_hash("push", sizeof("push"), SEED);
const int HASH_POP  = murmur_hash("pop",  sizeof("pop"),  SEED);
const int HASH_SUB  = murmur_hash("sub",  sizeof("sub"),  SEED);
const int HASH_ADD  = murmur_hash("add",  sizeof("add"),  SEED);

#define CMD(code, mnem, n_args)

#endif /* ASSEMBLY_H_ */
