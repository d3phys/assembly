#include <stdio.h>
#include <hash.h>
#include <string.h>

int main(int argc, char *argv[])
{
        for (int i = 1; i < argc; i++) {
                printf("%x\n", murmur_hash(argv[i], strlen(argv[i]), 0xDED64));
        }
                //printf("%x\n", murmur_hash(argc)

        return 0;
}
