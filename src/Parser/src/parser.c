/*
 *  Author:         Brett Heithold
 *  File:           parser.c
 *  Created on:     10/25/2020
 *  Last revision:  10/25/2020
 */


#include "../header/parser.h"
#include "../../Lexer/header/lexeme.h"


/********** Global Variables **********/
static Lexeme *currentLexeme;


/********** Public Function Definitions **********/

void check(char *type) {
    return getLexemeType(currentLexeme) == type;
}
