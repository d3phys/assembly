#ifndef THRW_H_
#define THRW_H_
#include <stdio.h>
#include <config.h>

#ifdef THRW_DEBUG
#define thrw(action, condition, fmt, ...)                                     \
        do {                                                                  \
                if (condition) {                                              \
                        fprintf(stderr, "thrw failed: " fmt "At %s %s: %d\n", \
                                ##__VA_ARGS__, __FILE__, __func__, __LINE__); \
                        action;                                               \
                }                                                             \
        } while (0)
#else
#define thrw(action, condition, fmt, ...)              \
        do {                                           \
                if (condition) {                       \
                        fprintf(stderr, "Error: " fmt, \
                                ##__VA_ARGS__);        \
                        action;                        \
                }                                      \
        } while (0)
#endif /* THRW_DEBUG */

#endif /* THRW_H_ */
