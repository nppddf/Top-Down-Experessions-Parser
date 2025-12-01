#ifndef UTILS_H
#define UTILS_H

const int MAX_BUFFER_LENGTH = 4096;

#define SOFT_ASSERT(cond, message, ret)                                                            \
    do {                                                                                           \
        if (!(cond)) {                                                                             \
            fprintf(stderr, "\ncondition `" #cond "` failed\n");                                   \
            perror((message));                                                                     \
            return (ret);                                                                          \
        }                                                                                          \
    } while (0)

#endif // UTILS_H
