/*
 *  Author:         Brett Heithold
 *  File:           lexer.c
 *  Created:        10/21/2020
 *  Last Revised:   10/22/2020
 */


#include "lexeme.h"
#include "lexer.h"
#include "types.h"

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
void growTokenAsNeeded(char *, int, int);
Lexeme *lexNumber(FILE *);
Lexeme *lexString(FILE *);
Lexeme *lexKeywordOrID(FILE *);


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
        default:
            if (isdigit(ch)) {
                ungetc(ch, fp);
                return lexNumber(fp);
            }
            /*
            else if (isalpha(ch)) {
                ungetc(ch, fp);
                return lexKeywordOrID(fp);
            }
            else if (ch == '\"') {
                return lexString(fp);
            }
            */
            else {
                return newLexeme(UNKNOWN, &ch);
            }
    }
    return newLexeme(BAD_CHARACTER, &ch);
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

void growTokenAsNeeded(char *token, int index, int length) {
    assert(token != NULL);
    assert(index >= 0);
    assert(length >= 0);

    if (index >= length) {
        int newLength = length * 2;
        token = realloc(token, sizeof(char) * newLength);
    }
}

Lexeme *lexNumber(FILE *fp) {
    int length = 1;
    int index = 0;
    char *token = malloc(sizeof(char) * length);
    bool isReal = false;

    char ch = fgetc(fp);
    while (!feof(fp) && (isdigit(ch) || ch == '.')) {
        if (ch == '.') {
            // if a dot has not yet been encountered,
            // set isReal to true and continue, else return BAD_NUMBER Lexeme
            if (!isReal) isReal = true;
            else return newLexeme(BAD_NUMBER, &ch);
        }

        // add character to token
        token[index++] = ch;

        // grow token as needed
        growTokenAsNeeded(token, index, length);

        // get next character
        ch = fgetc(fp);
    }

    // pushback character that broke the loop
    ungetc(ch, fp);

    // add termination character to the end of token
    token[index] = '\0';

    // return appropriate Lexeme
    return isReal ? newLexeme(REAL_TYPE, token) : newLexeme(INTEGER_TYPE, token);
}
