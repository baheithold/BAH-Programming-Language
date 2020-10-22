/*
 *  Author:         Brett Heithold
 *  File:           lexeme.c
 *  Created:        10/21/2020
 *  Last Revised:   10/21/2020
 */


#include "lexeme.h"
#include "types.h"


struct Lexeme {
    char    *type;
    char    *stringValue;
    int      integerValue;
    double   realValue;
    int      lineNumber;
};
