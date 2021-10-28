#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>

#include <iomap.h>

#include "executor.h"

int main(int argc, char *argv[])
{
        printf("Hello from cpu!!!\n");

        cpu_t cpu = {0};
        construct_cpu(&cpu);

        size_t size = 0;
        char *buf = nullptr;

        map_in(argv[1], &buf, &size);

        execute(&cpu, buf);

        munmap(buf, size);

        destruct_cpu(&cpu);

        return 0;
}
