/*
 *  Author:         Brett Heithold
 *  File:           prettyPrinter.c
 *  Created on:     11/11/2020
 *  Last revision:  11/13/2020
 */


#include "../header/prettyPrinter.h"
#include "../../lexer/header/lexeme.h"
#include "../../lexer/header/types.h"

#include <assert.h>
#include <stdio.h>


/********** Private Function Prototypes **********/
static void prettyProgram(FILE *, Lexeme *);
static void prettyImport(FILE *, Lexeme *);
static void prettyStatement(FILE *, Lexeme *);
static void prettyStatementList(FILE *, Lexeme *);
static void prettyVariableDefinition(FILE *, Lexeme *);
static void prettyFunctionDefinition(FILE *, Lexeme *);
static void prettyClassDefinition(FILE *, Lexeme *);
static void prettyFunctionCall(FILE *, Lexeme *);
static void prettyInheritance(FILE *, Lexeme *);
static void prettyInit(FILE *, Lexeme *);
static void prettyDimension(FILE *, Lexeme *);
static void prettyDimensionList(FILE *, Lexeme *);
static void prettyParameterList(FILE *, Lexeme *);
static void prettyVariableExpression(FILE *, Lexeme *);
static void prettyExpression(FILE *, Lexeme *);
static void prettyExpressionList(FILE *, Lexeme *);
static void prettyConditionalExpressionList(FILE *, Lexeme *);
static void prettyUnary(FILE *, Lexeme *);
static void prettyLambdaDefinition(FILE *, Lexeme *);
static void prettyBlock(FILE *, Lexeme *);
static void prettyForLoop(FILE *, Lexeme *);
static void prettyWhileLoop(FILE *, Lexeme *);
static void prettyIfStatement(FILE *, Lexeme *);
static void prettyElseStatement(FILE *, Lexeme *);
static void prettyReturnStatement(FILE *, Lexeme *);


/********** prettyPrint definition **********/

void prettyPrint(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    char *type = getLexemeType(tree);
    if (type == PROGRAM) prettyProgram(fp, tree);
    else if (type == IMPORT) prettyImport(fp, tree);
    else {
        fprintf(fp, "ERROR: Bad expression\n");
    }
}


/********** Private Function Definitions **********/

void prettyProgram(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    if (car(tree) != NULL) prettyPrint(fp, car(tree)); // imports
    if (cdr(tree) != NULL) prettyPrint(fp, cdr(tree)); // statements
}


void prettyImport(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    fprintf(fp, "import ");
    // print file path
    fprintf(fp, "\"%s\"\n", getLexemeStringValue(car(tree)));
}
