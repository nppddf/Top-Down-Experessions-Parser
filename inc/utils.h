#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

extern const int MAX_BUFFER_LENGTH;

#define SOFT_ASSERT(cond, message, ret)                                                            \
    do {                                                                                           \
        if (!(cond)) {                                                                             \
            fprintf(stderr, "\ncondition `" #cond "` failed\n");                                   \
            fprintf(stderr, "%s\n", (message));                                                    \
            return (ret);                                                                          \
        }                                                                                          \
    } while (0)

int removeNewlineCharacter(char *string);

#endif // UTILS_H
