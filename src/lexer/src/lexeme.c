/*
 *  Author:         Brett Heithold
 *  File:           lexeme.c
 *  Created:        10/21/2020
 *  Last Revised:   11/7/2020
 */


#include "../header/lexeme.h"
#include "../header/types.h"


#include <assert.h>
#include <stdlib.h>


/********** Global Constants **********/
#define DEBUG 0


struct Lexeme {
    char    *type;
    char    *stringValue;
    int      integerValue;
    double   realValue;
    int      lineNumber;
    Lexeme  *leftChild;
    Lexeme  *rightChild;
};


/********** Public Function Definitions **********/

Lexeme *newLexeme(char *type, char *value) {
    Lexeme *result = malloc(sizeof(Lexeme));
    assert(result != NULL);
    result->type = type;
    setLexemeValue(result, value);
    result->lineNumber = 0;
    result->leftChild = NULL;
    result->rightChild = NULL;
    return result;
}


char *getLexemeType(Lexeme *lexeme) {
    assert(lexeme != NULL);
    return lexeme->type;
}

void setLexemeType(Lexeme *lexeme, char *type) {
    assert(lexeme != NULL);
    lexeme->type = type;
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

void setLexemeValue(Lexeme *lexeme, char *str) {
    assert(lexeme != NULL);
    if (lexeme->type == INTEGER_TYPE) lexeme->integerValue = atoi(str);
    else if (lexeme->type == REAL_TYPE) lexeme->realValue = atof(str);
    else lexeme->stringValue = str;
}


int getLexemeLineNumber(Lexeme *lexeme) {
    assert(lexeme != NULL);
    return lexeme->lineNumber;
}


void setLexemeLineNumber(Lexeme *lexeme, int line) {
    assert(lexeme != NULL);
    lexeme->lineNumber = line;
}


Lexeme *cons(char *type, Lexeme *left, Lexeme *right) {
    assert(type != NULL);
    Lexeme *result = newLexeme(type, NULL);
    set_car(result, left);
    set_cdr(result, right);
    return result;
}


Lexeme *car(Lexeme *lexeme) {
    assert(lexeme != NULL);
    return lexeme->leftChild;
}


Lexeme *cdr(Lexeme *lexeme) {
    assert(lexeme != NULL);
    return lexeme->rightChild;
}


Lexeme *cadr(Lexeme *lexeme) {
    assert(lexeme != NULL);
    return car(cdr(lexeme));
}


Lexeme *set_car(Lexeme *parent, Lexeme *child) {
    assert(parent != NULL);
    parent->leftChild = child;
    return parent->leftChild;
}


Lexeme *set_cdr(Lexeme *parent, Lexeme *child) {
    assert(parent != NULL);
    parent->rightChild = child;
    return parent->rightChild;
}


void printLexeme(FILE *fp, Lexeme *lexeme) {
    assert(lexeme != NULL);

    // Change the DEBUG constant at the top of this file to enable
    if (DEBUG) {
        fprintf(fp, "Line %d: ", lexeme->lineNumber);
    }

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
