#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"
#include "parser_structures.h"
#include "utils.h"

// https://chatgpt.com/c/691b1d84-c6f8-8330-a481-97cd176f9473

int main(void) {
    char *inputBuffer = calloc(MAX_BUFFER_LENGTH, sizeof(char));

    printf("Enter the expression ( you can use integer numbers, +, - and '(' ')' ):\n> ");
    fgets(inputBuffer, MAX_BUFFER_LENGTH, stdin);
    inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

    Lexer lexer = {.currentToken = {TOKEN_JUNK}, .inputPointer = NULL, .inputPointerPosition = 0};
    lexerInit(&lexer, inputBuffer);

    Parser parser = {.lexer = NULL};
    parserInit(&parser, &lexer);

    ULL expressionResult = parseExpression(&parser);

    if (parser.lexer->currentToken.type != TOKEN_END) {
        printf("Incorrect expression.\n");
    }

    printf("%llu\n", expressionResult);

    free(inputBuffer);
    return 0;
}