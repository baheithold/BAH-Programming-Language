/*
 *  Author:         Brett Heithold
 *  File:           prettyPrinter.c
 *  Created on:     11/11/2020
 *  Last revision:  11/26/2020
 */


#include "../header/prettyPrinter.h"
#include "../../lexer/header/lexeme.h"
#include "../../lexer/header/types.h"

#include <assert.h>
#include <stdio.h>


/********** Private Function Prototypes **********/
static void prettyInteger(FILE *, Lexeme *);
static void prettyReal(FILE *, Lexeme *);
static void prettyString(FILE *, Lexeme *);
static void prettyBoolean(FILE *, Lexeme *);
static void prettyID(FILE *, Lexeme *);
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
static void prettyUnaryOperator(FILE *, Lexeme *);
static void prettyBinaryOperator(FILE *, Lexeme *);
static void prettyLogicalOperator(FILE *, Lexeme *);
static void prettyNot(FILE *, Lexeme *);
static void prettyComparator(FILE *, Lexeme *);
static void prettyJoin(FILE *, Lexeme *);
static void prettyParenthesizedExpression(FILE *, Lexeme *);


/********** prettyPrint definition **********/

void prettyPrint(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    char *type = getLexemeType(tree);
    if (type == INTEGER_TYPE) prettyInteger(fp, tree);
    else if (type == REAL_TYPE) prettyReal(fp, tree);
    else if (type == STRING_TYPE) prettyString(fp, tree);
    else if (type == BOOLEAN_TYPE) prettyBoolean(fp, tree);
    else if (type == ID_TYPE) prettyID(fp ,tree);
    else if (type == NULL_TYPE) fprintf(fp, "null");
    else if (type == PROGRAM) prettyProgram(fp, tree);
    else if (type == IMPORT) prettyImport(fp, tree);
    else if (type == STATEMENT) prettyStatement(fp, tree);
    else if (type == STATEMENT_LIST) prettyStatementList(fp, tree);
    else if (type == VARIABLE_DEFINITION) prettyVariableDefinition(fp, tree);
    else if (type == FUNCTION_CALL) prettyFunctionCall(fp, tree);
    else if (type == INIT) prettyInit(fp, tree);
    else if (type == DIMENSION) prettyDimension(fp, tree);
    else if (type == DIMENSION_LIST) prettyDimensionList(fp, tree);
    else if (type == PARAMETER_LIST) prettyParameterList(fp, tree);
    else if (type == VARIABLE_EXPRESSION) prettyVariableExpression(fp, tree);
    else if (type == EXPRESSION) prettyExpression(fp, tree);
    else if (type == EXPRESSION_LIST) prettyExpressionList(fp, tree);
    else if (type == UNARY) prettyUnary(fp, tree);
    else if (type == LAMBDA_DEFINITION) prettyLambdaDefinition(fp, tree);
    else if (type == BLOCK) prettyBlock(fp, tree);
    else if (type == UNARY_OPERATOR) prettyUnaryOperator(fp, tree);
    else if (type == BINARY_OPERATOR) prettyBinaryOperator(fp, tree);
    else if (type == LOGICAL_OPERATOR) prettyLogicalOperator(fp, tree);
    else if (type == NOT) prettyNot(fp, tree);
    else if (type == COMPARATOR) prettyComparator(fp, tree);
    else if (type == JOIN) prettyJoin(fp, tree);
    else if (type == OPAREN) prettyParenthesizedExpression(fp, tree);
    else {
        printLexeme(fp, tree);
        /* fprintf(fp, "ERROR: Bad expression"); */
    }
}


/********** Private Function Definitions **********/

void prettyInteger(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    fprintf(fp, "%d", getLexemeIntegerValue(tree));
}


void prettyReal(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    fprintf(fp, "%f", getLexemeRealValue(tree));
}


void prettyString(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    fprintf(fp, "\"%s\"", getLexemeStringValue(tree));
}


void prettyBoolean(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    fprintf(fp, "%s", getLexemeStringValue(tree));
}


void prettyID(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    fprintf(fp, "%s", getLexemeStringValue(tree));
}


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


void prettyStatement(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    prettyPrint(fp, car(tree));
    char *type = getLexemeType(car(tree));
    if (type == EXPRESSION || type == RETURN_STATEMENT || CONTINUE || BREAK) {
        fprintf(fp, ";");
    }
    printf("\n");
}


void prettyStatementList(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    while (tree != NULL) {
        prettyStatement(fp, car(tree));
        tree = cdr(tree);
    }
}


void prettyVariableDefinition(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    fprintf(fp, "var %s", getLexemeStringValue(car(tree)));
    if (cdr(tree) != NULL) prettyPrint(fp, cdr(tree));
}


void prettyFunctionCall(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    // print ID
    fprintf(fp, "%s", getLexemeStringValue(car(tree)));
    // print opening parantheses
    fprintf(fp, "(");
    // print expression list
    if (cdr(tree) != NULL) prettyPrint(fp, cdr(tree));
    // print closing parantheses
    fprintf(fp, ")");
}


void prettyInit(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    fprintf(fp, "=");
    prettyPrint(fp, car(tree));
}


void prettyDimension(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    prettyPrint(fp, car(tree));
}


void prettyDimensionList(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    fprintf(fp, "[");
    // print first item in dimension list
    prettyPrint(fp, car(tree));
    fprintf(fp, "]");
    // print remaining items in dimension list
    if (cdr(tree) != NULL) {
        prettyPrint(fp, cdr(tree));
    }
}



void prettyParameterList(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    // print the first id
    prettyPrint(fp, car(tree));
    // if there are more parameters, recursively print the remaining ids
    if (cdr(tree) != NULL) {
        fprintf(fp, ",");
        prettyPrint(fp, cdr(tree));
    }
}


void prettyVariableExpression(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    fprintf(fp, "%s", getLexemeStringValue(car(tree)));
    if (cdr(tree) != NULL) prettyPrint(fp, cdr(tree));
}


void prettyExpression(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    if (car(tree) != NULL) prettyPrint(fp, car(tree));
    if (cdr(tree) != NULL) prettyPrint(fp, cdr(tree));
}


void prettyExpressionList(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    // print first expression in the list
    prettyPrint(fp, car(tree));
    // if there are more expressions, print a comma and continue printing
    if (cdr(tree) != NULL) {
        fprintf(fp, ",");
        prettyPrint(fp, cdr(tree));
    }
}


void prettyUnary(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    if (car(tree) != NULL) prettyPrint(fp, car(tree));
    if (cdr(tree) != NULL) prettyPrint(fp, cdr(tree));
}


void prettyLambdaDefinition(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    fprintf(fp, "lambda(");
    // print parameter list
    prettyPrint(fp, car(tree));
    fprintf(fp, ")");
    // print block
    prettyPrint(fp, cdr(tree));
}


void prettyBlock(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    fprintf(fp, " {");
    // print the statement list
    if (car(tree) != NULL) prettyPrint(fp, car(tree));
    fprintf(fp, "}");
}


void prettyUnaryOperator(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    char *type = getLexemeType(tree);
    if (type == NEGATE_UNARY) fprintf(fp, "-");
    else if (type == INCREMENT_UNARY) fprintf(fp, "++");
    else if (type == DECREMENT_UNARY) fprintf(fp, "--");
    else fprintf(fp, "unknown unary operator");
}


void prettyBinaryOperator(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    char *type = getLexemeType(car(tree));
    if (type == PLUS_BINARY) fprintf(fp, "+");
    else if (type == MINUS_BINARY) fprintf(fp, "-");
    else if (type == TIMES_BINARY) fprintf(fp, "*");
    else if (type == DIVIDE_BINARY) fprintf(fp, "/");
    else if (type == POW_BINARY) fprintf(fp, "^");
    else if (type == MODULO_BINARY) fprintf(fp, "%%");
    else if (type == ASSIGN_BINARY) fprintf(fp, "=");
    else if (type == PLUS_ASSIGN_BINARY) fprintf(fp, "+=");
    else if (type == MINUS_ASSIGN_BINARY) fprintf(fp, "-=");
    else if (type == TIMES_ASSIGN_BINARY) fprintf(fp, "*=");
    else if (type == DIVIDE_ASSIGN_BINARY) fprintf(fp, "/=");
    else if (type == POW_ASSIGN_BINARY) fprintf(fp, "^=");
    else if (type == MODULO_ASSIGN_BINARY) fprintf(fp, "%%=");
    else if (type == DOT_BINARY) fprintf(fp, ".");
    else fprintf(fp, "unknown binary operator");
}


void prettyLogicalOperator(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    char *type = getLexemeType(tree);
    if (type == AND) fprintf(fp, "and");
    else if (type == OR) fprintf(fp, "or");
    else if (type == XOR) fprintf(fp, "xor");
    else fprintf(fp, "unknown logical operator");
}


void prettyNot(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    fprintf(fp, "!");
}


void prettyComparator(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    char *type = getLexemeType(tree);
    if (type == EQUALS_COMPARATOR) fprintf(fp, "==");
    else if (type == NOT_EQUALS_COMPARATOR) fprintf(fp, "!=");
    else if (type == GREATER_THAN_COMPARATOR) fprintf(fp, ">");
    else if (type == LESSER_THAN_COMPARATOR) fprintf(fp, "<");
    else if (type == GREATER_EQUALS_COMPARATOR) fprintf(fp, ">=");
    else if (type == LESSER_EQUALS_COMPARATOR) fprintf(fp, "<=");
    else fprintf(fp, "unknown comparator");
}


void prettyJoin(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    if (car(tree) != NULL) prettyPrint(fp, car(tree));
    if (cdr(tree) != NULL) prettyPrint(fp, cdr(tree));
}


void prettyParenthesizedExpression(FILE *fp, Lexeme *tree) {
    assert(tree != NULL);
    fprintf(fp, "(");
    prettyPrint(fp, car(tree));
    fprintf(fp, ")");
}
