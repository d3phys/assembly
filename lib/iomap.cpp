#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>

#include <iomap.h>
#include <thrw.h>

off_t get_size(const char *const file) 
{
        assert(file);
        errno = 0;

        struct stat buf = {};
        int err = stat(file, &buf);
        if (err)
                return -1;

        return buf.st_size;
}

int map_out(const char *file, char **const buf, const size_t size)
{
        assert(size);
        assert(file);
        errno = 0;

        const mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
        const int prot = PROT_READ | PROT_WRITE;
        char *bf = nullptr;
        int fd = -1;
        int err = 0;

        fd = open(file, O_RDWR | O_CREAT, mode); 
        thrw(goto finally, (fd == -1), 
            "Can't open the file %s: %s\n", file, strerror(errno));

        err = ftruncate(fd, size);
        thrw(goto finally, (err == -1), 
            "Can't truncate the file %s: %s\n", file, strerror(errno));

        bf = (char *)mmap(nullptr, size, prot, MAP_SHARED, fd, 0);
        thrw(goto finally, (buf == MAP_FAILED), 
            "Can't map the file %s: %s\n",  file, strerror(errno));

        *buf = bf;

finally:
        if (fd > 0)
                close(fd);

        return errno;
}

int map_in(const char *file, char **const buf, size_t *size)
{
        assert(size);
        assert(file);
        errno = 0;

        const int prot = PROT_READ | PROT_WRITE;
        char *bf = nullptr;
        int fd = -1;
        
        off_t fsz = get_size(file);
        thrw(goto finally, (fsz == -1), 
            "Can't get the file size: %s\n", strerror(errno));
        thrw(goto finally, (fsz == 0), 
            "File is empty: %s\n", file); 

        fd = open(file, O_RDWR); 
        thrw(goto finally, (fd <= 0), 
            "Can't open the file %s: %s\n", file, strerror(errno));

        bf = (char *)mmap(nullptr, fsz + 1, prot, MAP_PRIVATE, fd, 0);
        thrw(goto finally, (buf == MAP_FAILED), 
            "Can't map the file %s: %s\n",  file, strerror(errno));

        bf[fsz] = '\0';

        *size = fsz + 1;
        *buf = bf;

finally:
        if (fd > 0)
                close(fd);

        return errno;
}

