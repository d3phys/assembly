#include <string.h>
#include <stdio.h>

#include <hash.h>
#include <assembly.h>

int main(int argc, char *argv[])
{
        for (int i = 1; i < argc; i++)
                printf("%x\n", murmur_hash(argv[i], strlen(argv[i]), SEED));

        return 0;
}
