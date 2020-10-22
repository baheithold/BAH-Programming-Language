/*
 *  Author:         Brett Heithold
 *  File:           lexer.c
 *  Created:        10/21/2020
 *  Last Revised:   10/22/2020
 */


#include "lexeme.h"
#include "lexer.h"
#include "types.h"

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
Lexeme *lexNumber(FILE *);
Lexeme *lexString(FILE *);
Lexeme *lexIDorKeyword(FILE *);


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
        default:
            if (isdigit(ch)) {
                ungetc(ch, fp);
                return lexNumber(fp);
            }
            else if (isalpha(ch)) {
                ungetc(ch, fp);
                return lexIDorKeyword(fp);
            }
            else if (ch == '\"') {
                return lexString(fp);
            }
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
