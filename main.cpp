#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include "include/parse.h"
#include "include/compiler.h"

int main() 
{
        //printf("Page size: %d\n", getpagesize());
        printf("SIZE: %ld\n\n", sizeof("PUSH"));
        char *buf = nullptr;
        size_t n_bytes = 0;
        bufferise("test", &buf, &n_bytes);
        printf("Buffer adddress: %ld\n", (size_t)buf);
        //printf("%s\n", buf);

        code_t code = {0};
        construct_asm_code(&code, buf);

        for (int i = 0; i < code.n_cmds; i++)
                printf("Address: %ld | %d (len: %ld): %s\n", (size_t)code.cmds[i].start, i, code.cmds[i].len, code.cmds[i].start);

        printf("\n\n\n\n");
        compile_asm(&code, buf);
        free(code.cmds);
/*
        char *tok = buf;
        tok = strtik(tok, "\n");
        printf("Strtok: %s\n", tok);
        tok = strtik(nullptr, "\n");
        printf("Strtok: %s\n", tok);
        tok = strtik(nullptr, "\n");
        printf("Strtok: %s\n", tok);
        tok = strtik(nullptr, "\n");
        printf("Strtok: %s\n", tok);
        tok = strtik(nullptr, "\n");
        printf("Strtok: %s\n", tok);
        tok = strtik(nullptr, "\n");
        printf("Strtok: %s\n", tok);
        tok = strtik(nullptr, "\n");
        printf("Strtok: %s\n", tok);
        tok = strtik(nullptr, "\n");
        printf("Strtok: %s\n", tok);
        */

        int a = munmap(buf, n_bytes);

        return 0;
}
