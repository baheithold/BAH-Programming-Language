/*
 *  Author:         Brett Heithold
 *  File:           lexeme.c
 *  Created:        10/21/2020
 *  Last Revised:   10/23/2020
 */


#include "../header/lexeme.h"
#include "../header/types.h"


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
    else {
        result->stringValue = value;
    }
    result->lineNumber = 0;
    return result;
}


char *getLexemeType(Lexeme *lexeme) {
    assert(lexeme != NULL);
    return lexeme->type;
}


int getLexemeIntegerValue(Lexeme *lexeme) {
    assert(lexeme != NULL);
    return lexeme->integerValue;
}


double getLexemeRealValue(Lexeme *lexeme) {
    assert(lexeme != NULL);
    return lexeme->realValue;
}


char *getLexemeStringValue(Lexeme *lexeme) {
    assert(lexeme != NULL);
    return lexeme->stringValue;
}


int getLexemeLineNumber(Lexeme *lexeme) {
    assert(lexeme != NULL);
    return lexeme->lineNumber;
}


void setLexemeLineNumber(Lexeme *lexeme, int line) {
    assert(lexeme != NULL);
    lexeme->lineNumber = line;
}


void printLexeme(FILE *fp, Lexeme *lexeme) {
    assert(lexeme != NULL);

    if (lexeme->type == INTEGER_TYPE) {
        // Print INTEGER_TYPE Lexeme
        fprintf(fp, "%s %d", lexeme->type, lexeme->integerValue);
    }
    else if (lexeme->type == REAL_TYPE) {
        // Print REAL_TYPE Lexeme
        fprintf(fp, "%s %f", lexeme->type, lexeme->realValue);
    }
    else if (lexeme->type == STRING_TYPE) {
        // Print REAL_TYPE Lexeme
        fprintf(fp, "%s \"%s\"", lexeme->type, lexeme->stringValue);
    }
    else {
        fprintf(fp, "%s", lexeme->type);
        if (lexeme->stringValue != NULL) {
            fprintf(fp, " %s", lexeme->stringValue);
        }
    }
}
