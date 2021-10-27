#include <hash.h>
#include <assert.h>

unsigned int murmur_hash(const void *key, size_t len, unsigned int seed)
{
        const unsigned int mp = 0x5bd1e995;
        const int sft = 24;

        unsigned int hash = seed ^ (unsigned int)len;

        const unsigned char *data = (const unsigned char *)key;

        while (len >= 4) {
                unsigned int k = *(const unsigned int *)data;

                k *= mp;
                k ^= k >> sft;
                k *= mp;

                hash *= mp;
                hash ^= k;

                data += 4;
                len  -= 4;
        }

        unsigned int item = 0;
        switch (len) {
        case 3:
                item = (unsigned int)data[2];
                hash ^= item << 16;
                /* fall through */
        case 2:
                item = (unsigned int)data[1];
                hash ^= item << 8u;
                /* fall through */
        case 1:
                item = (unsigned int)data[0];
                hash ^= item;
                hash *= mp;
                break;
        case 0:
                break;
        default:
                assert(0);
        };

        hash ^= hash >> 13;
        hash *= mp;
        hash ^= hash >> 15;

        return hash;
} 
