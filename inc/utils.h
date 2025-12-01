#ifndef UTILS_H
#define UTILS_H

const int MAX_BUFFER_LENGTH = 4096;

#define SOFT_ASSERT(cond, msg, ret)                                                                \
    do {                                                                                           \
        if (!(cond)) {                                                                             \
            fprintf(stderr, "\ncondition `" #cond "` failed\n");                                   \
            perror((msg));                                                                         \
            return (ret);                                                                          \
        }                                                                                          \
    } while (0)

#endif // UTILS_H
