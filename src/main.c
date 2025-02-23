#include "files.h"
#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* strTokenType(TokenType type);  // temp
void printToken(Token token);  // temp

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    int return_code = 0;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s tokenize <filename>\n", argv[0]);
        return 1;
    }

    const char *command = argv[1];
    if (strcmp(command, "tokenize") == 0) {
        char *file_contents = readFile(argv[2]);
        if (file_contents == NULL) {
            return 1;
        }

        Scanner scanner;
        initScanner(&scanner, file_contents);
        while (1) {
            Token token = scanToken(&scanner);
            printToken(token);
            if (token.type == TOKEN_ERROR) {
                return_code = 65;
            }
            if (token.type == TOKEN_EOF) {
                break;
            }
        }

        free(file_contents);
    } else {
        fprintf(stderr, "Unknown command: %s\n", command);
        return 1;
    }
    return return_code;
}

void printToken(Token token) {
    if (token.type == TOKEN_ERROR) {
        fprintf(stderr, "[line %d] Error: %s\n", token.line, token.literal);
    } else {
        printf("%s %s %s\n", strTokenType(token.type), token.lexeme, token.literal ? token.literal : "null");
    }
}

const char* strTokenType(TokenType type) {
    switch (type) {
        case TOKEN_PLUS:
            return "PLUS";
        case TOKEN_MINUS:
            return "MINUS";
        case TOKEN_STAR:
            return "STAR";
        case TOKEN_SLASH:
            return "SLASH";
        case TOKEN_EQUAL:
            return "EQUAL";
        case TOKEN_LEFT_PAREN:
            return "LEFT_PAREN";
        case TOKEN_RIGHT_PAREN:
            return "RIGHT_PAREN";
        case TOKEN_IDENTIFIER:
            return "IDENTIFIER";
        case TOKEN_NUMBER:
            return "NUMBER";
        case TOKEN_AS:
            return "AS";
        case TOKEN_ANAGNOSI:
            return "ANAGNOSI";
        case TOKEN_GRAFO:
            return "GRAFO";
        case TOKEN_MUNUS:
            return "MUNUS";
        case TOKEN_SINON:
            return "SINON";
        case TOKEN_EOF:
            return "EOF";
    }
}
