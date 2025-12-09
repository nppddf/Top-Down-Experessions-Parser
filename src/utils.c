#include <utils.h>
#include <stdlib.h>
#include <string.h>

const int MAX_BUFFER_LENGTH = 4096;

int removeNewlineCharacter(char *string) {
    SOFT_ASSERT(string != NULL, "Failed to transfer a pointer.\n", EXIT_FAILURE);

    string[strcspn(string, "\n")] = '\0';

    return EXIT_SUCCESS;
}