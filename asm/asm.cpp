#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "compiler.h"
#include "parse.h"
#include <assembly.h>
#include <thrw.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
        code_t code = {0};
        size_t size = 0;
        char *buf = nullptr;
        FILE *out = nullptr;

        fmap(argv[1], &buf, &size);
        out = fopen(argv[2], "w");

        construct_asm_code(&code, buf);
        preprocess_asm(&code, out);

        fclose(out);
        if (buf)
                munmap(buf, size);
        destruct_asm_code(&code);

        char file[] = "output";
        char *outbuf = nullptr;
        size_t written = 0;

        map_in(argv[2], &buf, &size);
        construct_asm_code(&code, buf);
        size_t fsize = code.n_cmds * (sizeof(cmd_t) + sizeof(arg_t));
        printf("Size: %lu\n", fsize);
        map_out(file, &outbuf, fsize);
        perror("Map out");
        compile_asm(&code, outbuf, &written);

        munmap(outbuf, fsize);
        if (buf)
                munmap(buf, size);

        truncate(file, written);
exit:
        destruct_asm_code(&code);

        return 0;
}
