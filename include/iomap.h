#ifndef MAPIO_H_
#define MAPIO_H_

#include <stddef.h>

off_t get_size(const char *const file);

int map_out(const char *file, char **const buf, const size_t size);
int map_in (const char *file, char **const buf, size_t *size);

#endif /* MAPIO_H_ */
