#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>

#include <iomap.h>
#include "executor.h"

int main(int argc, char *argv[])
{
        thrw(exit(1), (argc != 2), "Invalid arguments count\n");

        int error = 0;

        cpu_t cpu = {0};
        char *buf = nullptr;

        size_t size = 0;

        error = construct_cpu(&cpu);
        thrw(goto cup1, (error), "Can't create cpu\n");

        error = map_in(argv[1], &buf, &size);
        thrw(goto cup1, (error), "Can't map binary file\n");

        error = execute(&cpu, buf);
        thrw(goto cup2, (error), "Error during execution\n");

cup2:
        munmap(buf, size);
cup1:
        destruct_cpu(&cpu);

        return 0;
}


