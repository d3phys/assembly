#ifndef THRW_H_
#define THRW_H_
#include <stdio.h>

#define thrw(to, condition, fmt, ...)                                    \
        do {                                                             \
                if (condition) {                                         \
                        fprintf(stderr, "[at %16s (%3d)]>>> "               \
                                fmt, __func__, __LINE__, ##__VA_ARGS__); \
                        goto to;                                         \
                }                                                        \
        } while (0)

#endif /* THRW_H_ */
