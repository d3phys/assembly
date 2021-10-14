#include "include/hash.h"

unsigned int murmur_hash(const void *const key, int len, unsigned int seed)
{
        const unsigned int mp = 0x5bd1e995;
        const int sft = 24;

        unsigned int hash = seed ^ len;

        const unsigned char *data = (const unsigned char *)key;

        while (len >= 4) {
                unsigned int k = *(unsigned int *)data;

                k *= mp;
                k ^= k >> sft;
                k *= mp;

                hash *= mp;
                hash ^= k;

                data += 4;
                len  -= 4;
        }

        switch (len) {
        case 3:
                hash ^= data[2] << 16;
        case 2:
                hash ^= data[1] << 8;
        case 1:
                hash ^= data[0];

                hash *= mp;
        };

        hash ^= hash >> 13;
        hash *= mp;
        hash ^= hash >> 15;

        return hash;
} 
