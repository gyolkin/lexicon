#include "scanner.h"
#include "utils.h"

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static bool isAtEnd(Scanner* scanner) {
    return *scanner->current == '\0';
}

static char advance(Scanner* scanner) {
    scanner->current++;
    return scanner->current[-1];
}

static char peek(Scanner* scanner) {
    return *scanner->current;
}

static char peekNext(Scanner* scanner) {
    if (isAtEnd(scanner)) return '\0';
    return scanner->current[1];
}

static bool match(Scanner* scanner, char expected) {
    if (isAtEnd(scanner)) return false;
    if (*scanner->current != expected) return false;
    scanner->current++;
    return true;
}

static Token makeToken(Scanner* scanner, TokenType type) {
    Token token;
    token.type = type;
    token.line = scanner->line;
    token.lexeme = strndup(scanner->start, (int)(scanner->current - scanner->start));
    token.literal = NULL;
    return token;
}

static Token makeTokenWithLiteral(Scanner* scanner, TokenType type, const char* literal) {
    Token token = makeToken(scanner, type);
    token.literal = strndup(literal, strlen(literal));
    return token;
}

static void skipWhitespace(Scanner* scanner) {
    while (true) {
        char c = peek(scanner);
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance(scanner);
                break;
            case '\n':
                scanner->line++;
                advance(scanner);
                break;
            case '/':
                if (peekNext(scanner) == '/') {
                    while (peek(scanner) != '\n' && !isAtEnd(scanner)) {
                        advance(scanner);
                    }
                } else {
                    return;
                }
                break;
            default:
                return;
        }
    }
}

static bool isRomanChar(char c) {
    return c == 'I' || c == 'V' || c == 'X' ||
           c == 'L' || c == 'C' || c == 'D' ||
           c == 'M' || c == 'N';
}

static TokenType identifierType(const char* text, int length) {
    switch (text[0]) {
        case 'A':
            if (length == 2 && strncmp(text, "As", 2) == 0) return TOKEN_AS;
            if (length == 8 && strncmp(text, "Anagnosi", 8) == 0) return TOKEN_ANAGNOSI;
            break;
        case 'G':
            if (length == 5 && strncmp(text, "Grafo", 5) == 0) return TOKEN_GRAFO;
            break;
        case 'M':
            if (length == 5 && strncmp(text, "Munus", 5) == 0) return TOKEN_MUNUS;
            break;
        case 'S':
            if (length == 5 && strncmp(text, "Sinon", 5) == 0) return TOKEN_SINON;
            break;
    }
    return TOKEN_IDENTIFIER;
}

static Token scanRomanNumeral(Scanner* scanner) {
    while (isupper(peek(scanner))) {
        char c = peek(scanner);
        if (!isRomanChar(c)) break;
        advance(scanner);
    }
    int length = (int)(scanner->current - scanner->start);
    if (length > 1) {
        for (const char* p = scanner->start; p < scanner->current; p++) {
            if (*p == 'N') {
                return makeTokenWithLiteral(scanner, TOKEN_ERROR, "Incorrect Roman numeral: 'N' is not allowed");
            }
        }
    }
    int arabicValue = romanToArabic(scanner->start, length);
    char literal[12];
    snprintf(literal, sizeof(literal), "%d", arabicValue);
    return makeTokenWithLiteral(scanner, TOKEN_NUMBER, literal);
}

static Token scanIdentifier(Scanner* scanner) {
    while (isalpha(peek(scanner))) {
        advance(scanner);
    }
    int length = (int)(scanner->current - scanner->start);
    if (isupper(scanner->start[0])) {
        return makeToken(scanner, identifierType(scanner->start, length));
    }
    return makeToken(scanner, TOKEN_IDENTIFIER);
}

void initScanner(Scanner* scanner, const char* source) {
    scanner->start = source;
    scanner->current = source;
    scanner->line = 1;
}

Token scanToken(Scanner* scanner) {
    skipWhitespace(scanner);
    scanner->start = scanner->current;
    if (isAtEnd(scanner)) return makeToken(scanner, TOKEN_EOF);
    char c = advance(scanner);
    if (isalpha(c)) {
        if (isupper(c)) {
            if (!isAtEnd(scanner) && islower(peek(scanner))) {
                return scanIdentifier(scanner);
            } else {
                return scanRomanNumeral(scanner);
            }
        } else {
            return scanIdentifier(scanner);
        }
    }
    switch (c) {
        case '+': return makeToken(scanner, TOKEN_PLUS);
        case '-': return makeToken(scanner, TOKEN_MINUS);
        case '*': return makeToken(scanner, TOKEN_STAR);
        case '/':
            if (match(scanner, '/')) {
                while (peek(scanner) != '\n' && !isAtEnd(scanner)) {
                    advance(scanner);
                }
                return scanToken(scanner);
            } else {
                return makeToken(scanner, TOKEN_SLASH);
            }
        case '=': return makeToken(scanner, TOKEN_EQUAL);
        case '(': return makeToken(scanner, TOKEN_LEFT_PAREN);
        case ')': return makeToken(scanner, TOKEN_RIGHT_PAREN);
    }
    return makeTokenWithLiteral(scanner, TOKEN_ERROR, "Unexpected character.");
}
