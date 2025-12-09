#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"

int main(void) {
    char buffer[MAX_BUFFER_LENGTH];

    printf("Enter the expression (+, -, round brackets):\n");
    printf("> ");

    SOFT_ASSERT(fgets(buffer, (int)sizeof(buffer), stdin) != NULL, "Failed to get the line.\n",
                EXIT_FAILURE);
    buffer[strcspn(buffer, "\n")] = '\0';

    Lexer lexer;
    SOFT_ASSERT(initializeLexer(&lexer, buffer) == EXIT_SUCCESS, "Failed to initialize the lexer.\n", EXIT_FAILURE);

    Parser parser;
    initializeParser(&parser, &lexer);

    ASTNode *root = parserParse(&parser);

    if (parser.isError) {
        printErrorParser(&parser);
        freeASTNode(root);
        return EXIT_FAILURE;
    }

    printASTNode(root);
    freeASTNode(root);

    return 0;
}
