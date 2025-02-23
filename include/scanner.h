#pragma once

typedef enum {
    TOKEN_PLUS,             // +
    TOKEN_MINUS,            // -
    TOKEN_STAR,             // *
    TOKEN_SLASH,            // /
    TOKEN_EQUAL,            // =
    TOKEN_LEFT_PAREN,       // (
    TOKEN_RIGHT_PAREN,      // )

    TOKEN_IDENTIFIER,       // variable names
    TOKEN_NUMBER,           // roman numerals

    TOKEN_AS,               // "As"
    TOKEN_ANAGNOSI,         // "Anagnosi"
    TOKEN_GRAFO,            // "Grafo"
    TOKEN_MUNUS,            // "Munus"
    TOKEN_SINON,            // "Sinon"

    TOKEN_EOF,              // end of file
    TOKEN_ERROR             // error
} TokenType;

typedef struct {
    TokenType type;
    int line;
    const char* lexeme;
    const char* literal;
} Token;

typedef struct {
    const char* start;
    const char* current;
    int line;
} Scanner;

void initScanner(Scanner* scanner, const char* source);
Token scanToken(Scanner* scanner);
