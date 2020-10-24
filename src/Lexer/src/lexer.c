/*
 *  Author:         Brett Heithold
 *  File:           lexer.c
 *  Created:        10/21/2020
 *  Last Revised:   10/23/2020
 */


#include "../header/lexeme.h"
#include "../header/lexer.h"
#include "../header/types.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/********** Global Variables **********/

static int currentLine = 1;


/********** Private Function Prototypes **********/

void skipWhiteSpace(FILE *);
void skipComment(FILE *);
bool commentPending(char);
bool numberPending(char);
char peek(FILE *);
Lexeme *lexNumber(FILE *);
Lexeme *lexString(FILE *);
Lexeme *lexKeywordOrID(FILE *);
bool isValidSymbol(char);
bool isValidCharacterForID(char);


/********** Public Function Definitions **********/

Lexeme *lex(FILE *fp) {
    skipWhiteSpace(fp);
    char ch = fgetc(fp);
    if (ch == EOF) {
        return newLexeme(END_OF_INPUT, NULL);
    }
    switch (ch) {
        case '(': return newLexeme(OPAREN, NULL);
        case ')': return newLexeme(CPAREN, NULL);
        case '{': return newLexeme(OBRACE, NULL);
        case '}': return newLexeme(CBRACE, NULL);
        case ',': return newLexeme(COMMA, NULL);
        case ';': return newLexeme(SEMICOLON, NULL);
        case ':': return newLexeme(COLON, NULL);
        case '.':
            if (isdigit(peek(fp))) {
                ungetc(ch, fp);
                return lexNumber(fp);
            }
            else return newLexeme(DOT_BINARY, NULL);
        case '+':
            ch = fgetc(fp);
            switch (ch) {
                case '+': return newLexeme(INCREMENT_UNARY, NULL);
                case '=': return newLexeme(PLUS_ASSIGN_BINARY, NULL);
                default:
                    ungetc(ch, fp);
                    return newLexeme(PLUS_BINARY, NULL);
            }
        case '-':
            ch = fgetc(fp);
            switch (ch) {
                case '-': return newLexeme(DECREMENT_UNARY, NULL);
                case '=': return newLexeme(MINUS_ASSIGN_BINARY, NULL);
                default:
                    ungetc(ch, fp);
                    return newLexeme(MINUS_BINARY, NULL);
            }
        case '*':
            ch = fgetc(fp);
            switch (ch) {
                case '=': return newLexeme(TIMES_ASSIGN_BINARY, NULL);
                default:
                    ungetc(ch, fp);
                    return newLexeme(TIMES_BINARY, NULL);
            }
        case '/':
            ch = fgetc(fp);
            switch (ch) {
                case '=': return newLexeme(DIVIDE_ASSIGN_BINARY, NULL);
                default:
                    ungetc(ch, fp);
                    return newLexeme(DIVIDE_BINARY, NULL);
            }
        case '^':
            ch = fgetc(fp);
            switch (ch) {
                case '=': return newLexeme(POW_ASSIGN_BINARY, NULL);
                default:
                    ungetc(ch, fp);
                    return newLexeme(POW_BINARY, NULL);
            }
        case '%':
            ch = fgetc(fp);
            switch (ch) {
                case '=': return newLexeme(MODULO_ASSIGN_BINARY, NULL);
                default:
                    ungetc(ch, fp);
                    return newLexeme(MODULO_BINARY, NULL);
            }
        case '<':
            ch = fgetc(fp);
            switch (ch) {
                case '=': return newLexeme(LESSER_EQUALS_COMPARATOR, NULL);
                default:
                    ungetc(ch, fp);
                    return newLexeme(LESSER_THAN_COMPARATOR, NULL);
            }
        case '>':
            ch = fgetc(fp);
            switch (ch) {
                case '=': return newLexeme(GREATER_EQUALS_COMPARATOR, NULL);
                default:
                    ungetc(ch, fp);
                    return newLexeme(GREATER_THAN_COMPARATOR, NULL);
            }
        case '=':
            ch = fgetc(fp);
            switch (ch) {
                case '=': return newLexeme(EQUALS_COMPARATOR, NULL);
                default:
                    ungetc(ch, fp);
                    return newLexeme(ASSIGN_BINARY, NULL);
            }
        case '!':
            ch = fgetc(fp);
            switch (ch) {
                case '=': return newLexeme(NOT_EQUALS_COMPARATOR, NULL);
                default:
                    ungetc(ch, fp);
                    return newLexeme(NEGATE_UNARY, NULL);
            }
        default:
            if (isdigit(ch)) {
                ungetc(ch, fp);
                return lexNumber(fp);
            }
            else if (isalpha(ch) || isValidSymbol(ch)) {
                ungetc(ch, fp);
                return lexKeywordOrID(fp);
            }
            else if (ch == '\"') {
                return lexString(fp);
            }
            else {
                return newLexeme(UNKNOWN, NULL);
            }
    }
    char *chStr = malloc(sizeof(char) * 2);
    chStr[0] = ch;
    chStr[1] = '\0';
    return newLexeme(BAD_CHARACTER, chStr);
}

int getLexerLineNumber(void) {
    return currentLine;
}


/********** Private Function Definitions **********/

void skipWhiteSpace(FILE *fp) {
    char ch = fgetc(fp);
    while (isspace(ch)) {
        if (ch == '\n') currentLine++;
        ch = fgetc(fp);
    }
    if (commentPending(ch)) {
        skipComment(fp);
        skipWhiteSpace(fp);
    }
    else ungetc(ch, fp);
}

void skipComment(FILE *fp) {
    char ch = fgetc(fp);
    while (ch != '\n') {
        ch = fgetc(fp);
    }
}

bool commentPending(char ch) {
    return ch == '#';
}

bool numberPending(char ch) {
    return isdigit(ch);
}

char peek(FILE *fp) {
    char ch = fgetc(fp);
    ungetc(ch, fp);
    return ch;
}

Lexeme *lexNumber(FILE *fp) {
    int length = 1;
    int index = 0;
    char *token = malloc(sizeof(char) * length);
    assert(token != NULL);
    bool isReal = false;

    char ch = fgetc(fp);
    while (!feof(fp) && (isdigit(ch) || ch == '.')) {
        if (ch == '.') {
            // if a dot has not yet been encountered,
            // set isReal to true and continue, else return BAD_NUMBER Lexeme
            if (!isReal) isReal = true;
            else {
                char *chStr = malloc(sizeof(char) * 2);
                chStr[0] = ch;
                chStr[1] = '\0';
                return newLexeme(BAD_NUMBER, chStr);
            }
        }

        // add character to token
        token[index++] = ch;

        // grow token as needed
        if (index >= length) {
            length *= 2;
            token = realloc(token, length);
        }

        // get next character
        ch = fgetc(fp);
    }

    // pushback character that broke the loop
    ungetc(ch, fp);

    // add termination character to the end of token
    token[index] = '\0';

    // shrink token length to fit
    token = realloc(token, sizeof(char) * (index + 1));
    assert(token != NULL);

    // return appropriate Lexeme
    return isReal ? newLexeme(REAL_TYPE, token) : newLexeme(INTEGER_TYPE, token);
}

Lexeme *lexString(FILE *fp) {
    int length = 1;
    int index = 0;
    char *str = malloc(sizeof(char) * length);
    assert(str != NULL);

    char ch = fgetc(fp);
    while (ch != '\"') {
        if (ch == EOF) {
            ungetc(ch, fp);
            return newLexeme(BAD_STRING, NULL);
        }
        else if (ch == '\\') {
            // handle escape character
            ch = fgetc(fp);
        }
        str[index++] = ch;
        if (index >= length) {
            length *= 2;
            str = realloc(str, length);
        }
        ch = fgetc(fp);
    }

    // add termination character to the end of token
    str[index] = '\0';

    // shrink token length to fit
    str = realloc(str, sizeof(char) * (index + 1));
    assert(str != NULL);

    return newLexeme(STRING_TYPE, str);
}

Lexeme *lexKeywordOrID(FILE *fp) {
    int length = 1;
    int index = 0;
    char *token = malloc(sizeof(char) * length);
    assert(token != NULL);

    char ch = fgetc(fp);
    while (!feof(fp) && isValidCharacterForID(ch)) {
        token[index++] = ch;
        if (index >= length) {
            length *= 2;
            token = realloc(token, length);
        }
        ch = fgetc(fp);
    }

    // pushback character that broke the loop
    ungetc(ch, fp);

    // add termination character to the end of token
    token[index] = '\0';

    // shrink token length to fit
    token = realloc(token, sizeof(char) * (index + 1));
    assert(token != NULL);

    // return appropriate Lexeme
    if (strcmp(token, "if") == 0) return newLexeme(IF, token);
    else if (strcmp(token, "else") == 0) return newLexeme(ELSE, token);
    else if (strcmp(token, "for") == 0) return newLexeme(FOR, token);
    else if (strcmp(token, "while") == 0) return newLexeme(WHILE, token);
    else if (strcmp(token, "function") == 0) return newLexeme(FUNCTION, token);
    else if (strcmp(token, "var") == 0) return newLexeme(VAR, token);
    else if (strcmp(token, "return") == 0) return newLexeme(RETURN, token);
    else if (strcmp(token, "break") == 0) return newLexeme(BREAK, token);
    else if (strcmp(token, "continue") == 0) return newLexeme(CONTINUE, token);
    else if (strcmp(token, "class") == 0) return newLexeme(CLASS, token);
    else if (strcmp(token, "lambda") == 0) return newLexeme(LAMBDA, token);
    else if (strcmp(token, "void") == 0) return newLexeme(VOID, token);
    else if (strcmp(token, "true") == 0) return newLexeme(BOOLEAN_TYPE, token);
    else if (strcmp(token, "false") == 0) return newLexeme(BOOLEAN_TYPE, token);
    else if (strcmp(token, "null") == 0) return newLexeme(NULL_TYPE, token);
    else if (strcmp(token, "and") == 0) return newLexeme(AND, token);
    else if (strcmp(token, "or") == 0) return newLexeme(OR, token);
    else if (strcmp(token, "xor") == 0) return newLexeme(XOR, token);
    else return newLexeme(ID_TYPE, token);
}

bool isValidSymbol(char ch) {
    switch (ch) {
        case '_':
        case '?':
        case '@':
        case '&':
        case '~':
            return true;
        default:
            return false;
    }
}

bool isValidCharacterForID(char ch) {
    return isalpha(ch) || isdigit(ch) || isValidSymbol(ch);
}
