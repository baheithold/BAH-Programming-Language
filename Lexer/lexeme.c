/*
 *  Author:         Brett Heithold
 *  File:           lexeme.c
 *  Created:        10/21/2020
 *  Last Revised:   10/21/2020
 */


#include "lexeme.h"
#include "types.h"


#include <assert.h>
#include <stdlib.h>


struct Lexeme {
    char    *type;
    char    *stringValue;
    int      integerValue;
    double   realValue;
    int      lineNumber;
};


/********** Public Function Definitions **********/

Lexeme *newLexeme(char *type, char *value) {
    assert(type != NULL);
    Lexeme *result = malloc(sizeof(Lexeme));
    assert(result != NULL);
    result->type = type;
    if (type == INTEGER_TYPE) {
        result->integerValue = atoi(value);
    }
    else if (type == REAL_TYPE) {
        result->realValue = atof(value);
    }
    else if (type == STRING_TYPE) {
        result->stringValue = value;
    }
    result->lineNumber = 0;
    return result;
}
