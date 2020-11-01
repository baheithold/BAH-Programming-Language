/*
 *  Author:         Brett Heithold
 *  File:           environment.c
 *  created on:     10/31/2020
 *  Last Revision:  11/1/2020
 */


#include "../header/environment.h"
#include "../../lexer/header/lexeme.h"


/********** Private Function Prototypes **********/
Lexeme *cons(char *, Lexeme *, Lexeme *);
Lexeme *car(Lexeme *);
Lexeme *cdr(Lexeme *);
void    setCar(Lexeme *, Lexeme *);
void    setCdr(Lexeme *, Lexeme *);


/********** Public Function Definitions **********/

Lexeme *createEnvironment(void) {
    return cons(ENVIRONMENT, NULL, cons(VALUES, NULL, NULL));
}


/********** Private Function Definitions **********/

Lexeme *cons(char *type, Lexeme *left, Lexeme *right) {
    assert(type != NULL);
    Lexeme *result = newLexeme(type, NULL);
}

Lexeme *car(Lexeme *lexeme) {
    assert(lexeme != NULL);
    return getLexemeLeftChild(lexeme);
}

Lexeme *cdr(Lexeme *lexeme) {
    assert(lexeme != NULL);
    return getLexemeRightChild(lexeme);
}
