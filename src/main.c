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
    SOFT_ASSERT(removeNewlineCharacter(buffer) == EXIT_SUCCESS,
                "Failed to remove the newline character.\n", EXIT_FAILURE);

    Lexer lexer;
    SOFT_ASSERT(initializeLexer(&lexer, buffer) == EXIT_SUCCESS,
                "Failed to initialize the lexer.\n", EXIT_FAILURE);

    Parser parser;
    SOFT_ASSERT(initializeParser(&parser, &lexer) == EXIT_SUCCESS,
                "Failed to initialize the parser.\n", EXIT_FAILURE);

    ASTNode *root = parserParse(&parser);
    SOFT_ASSERT(root != NULL, "Failed to parse via parser.\n", EXIT_FAILURE);

    if (parser.isError) {
        printErrorParser(&parser);
        freeASTNode(root);
        return EXIT_FAILURE;
    }

    printASTResult(root);
    freeASTNode(root);

    return 0;
}
