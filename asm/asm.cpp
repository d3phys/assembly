#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "compiler.h"
#include "parse.h"
#include <assembly.h>
#include <thrw.h>

int main(int argc, char *argv[])
{
        code_t code = {0};
        size_t size = 0;
        char *buf = nullptr;
        FILE *out = nullptr;

        thrw(exit, (argc < 3),
             "Invalid arguments count\n");

        fmap(argv[1], &buf, &size);
        out = fopen(argv[2], "w");

        construct_asm_code(&code, buf);
        preprocess_asm(&code, out);


exit:
        if (buf)
                munmap(buf, size);
        destruct_asm_code(&code);

        return 0;
}
