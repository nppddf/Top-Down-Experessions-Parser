#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "ast.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"

int main(void) {
    char buffer[MAX_BUFFER_LENGTH];

    printf("Enter the expression (+, -, round brackets). Empty string - exit.\n");

    while (true) {
        printf("> ");
        if (!fgets(buffer, (int)sizeof(buffer), stdin)) {
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0'; // TODO: make abstract function

        if (buffer[0] == '\0') {
            break;
        } // TODO: make abstract function

        // TODO: think about the logic
        Lexer lexer;
        initializeLexer(&lexer, buffer);

        Parser parser;
        initializeParser(&parser, &lexer);

        AstNode *root = parserParse(&parser);

        if (parser.error) {
            printErrorParser(&parser);
        } else {
            printASTNode(root);
        }

        freeASTNode(root);
    }

    return 0;
}
