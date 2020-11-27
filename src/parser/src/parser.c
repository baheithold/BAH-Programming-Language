/*
 *  Author:         Brett Heithold
 *  File:           parser.c
 *  Created on:     10/25/2020
 *  Last revision:  11/26/2020
 */


#include "../header/parser.h"
#include "../../lexer/header/lexeme.h"
#include "../../lexer/header/lexer.h"
#include "../../lexer/header/types.h"

#include <assert.h>
#include <stdlib.h>


#define DEBUG false


/********** Global Variables **********/
static Lexeme *currentLexeme;


/********** Grammar Function Definitions **********/

bool check(char *type) {
    return getLexemeType(currentLexeme) == type;
}

void advance(void) {
    currentLexeme = lex();
}

Lexeme *match(char *type) {
    assert(type != NULL);
    matchNoAdvance(type);
    Lexeme *result = currentLexeme;
    advance();
    return result;
}

void matchNoAdvance(char *type) {
    assert(type != NULL);
    assert(currentLexeme != NULL);
    if (!check(type)) {
        fprintf(stdout, "ERROR, line %d: ", getLexemeLineNumber(currentLexeme));
        fprintf(stdout, "expected %s, but encountered %s\n", type, getLexemeType(currentLexeme));
        exit(0);
    }
}


/********** Grammar Function Definitions **********/

Lexeme *program(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: program\n");
    }
    if (importPending()) {
        Lexeme *i = import();
        Lexeme *tree = program();
        return cons(PROGRAM, cons(IMPORT, i, NULL), tree);
    }
    else if (statementListPending()) {
        return cons(PROGRAM, NULL, statementList());
    }
}

Lexeme *import(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: import\n");
    }
    match(IMPORT);
    return match(STRING_TYPE);
}

Lexeme *statement(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: statement\n");
    }
    if (definitionPending()) {
        Lexeme *d = definition();
        return cons(STATEMENT, d, NULL);
    }
    else if (expressionPending()) {
        Lexeme *e = expression();
        match(SEMICOLON);
        return cons(STATEMENT, e, NULL);
    }
    else if (loopPending()) {
        return cons(STATEMENT, loop(), NULL);
    }
    else if (ifStatementPending()) {
        return cons(STATEMENT, ifStatement(), NULL);
    }
    else if (returnStatementPending()) {
        Lexeme *rs = returnStatement();
        match(SEMICOLON);
        return cons(STATEMENT, rs, NULL);
    }
    else if (check(CONTINUE)) {
        match(CONTINUE);
        match(SEMICOLON);
        return cons(STATEMENT, newLexeme(CONTINUE, NULL), NULL);
    }
    else if (check(BREAK)) {
        match(BREAK);
        match(SEMICOLON);
        return cons(STATEMENT, newLexeme(BREAK, NULL), NULL);
    }
    return NULL;
}

Lexeme *statementList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: statementList\n");
    }
    if (statementPending()) {
        Lexeme *s = statement();
        Lexeme *sList = optStatementList();
        return cons(STATEMENT_LIST, s, sList);
    }
    return NULL;
}

Lexeme *optStatementList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: optStatementList\n");
    }
    if (statementListPending()) {
        return statementList();
    }
    return NULL;
}

Lexeme *definition(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: definition\n");
    }
    if (variableDefinitionPending()) {
        Lexeme *vdef = variableDefinition();
        match(SEMICOLON);
        return vdef;
    }
    else if (functionDefinitionPending()) {
        return functionDefinition();
    }
    else if (classDefinitionPending()) {
        return classDefinition();
    }
    return NULL;
}

Lexeme *variableDefinition(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: variableDefinition\n");
    }
    match(VAR);
    Lexeme *id = match(ID_TYPE);
    Lexeme *tree = optInit();
    return cons(VARIABLE_DEFINITION, id, tree);
}

Lexeme *functionDefinition(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: functionDefinition\n");
    }
    match(FUNCTION);
    Lexeme *id = match(ID_TYPE);
    match(OPAREN);
    Lexeme *pList = NULL;
    Lexeme *b = NULL;
    if (parameterListPending()) {
        pList = parameterList();
        match(CPAREN);
        b = block();
    }
    else {
        match(VOID);
        match(CPAREN);
        b = block();
    }
    return cons(FUNCTION_DEFINITION, cons(JOIN, id, pList), b);
}

Lexeme *classDefinition(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: classDefinition\n");
    }
    match(CLASS);
    match(ID_TYPE);
    optInheritance();
    block();
}

Lexeme *optInheritance(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: oprtInheritance\n");
    }
    if (check(COLON)) {
        match(COLON);
        match(ID_TYPE);
    }
}

Lexeme *optInit(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: optInit\n");
    }
    if (check(ASSIGN_BINARY)) {
        match(ASSIGN_BINARY);
        if (expressionPending()) {
            Lexeme *e = expression();
            return cons(INIT, e, NULL);
        }
        else {
            matchNoAdvance("expression");
        }
    }
    return NULL;
}

Lexeme *dimension(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: dimension\n");
    }
    match(OBRACKET);
    Lexeme *eList = optExpressionList();
    match(CBRACKET);
    return cons(DIMENSION, eList, NULL);
}


Lexeme *dimensionList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: dimensionList\n");
    }
    Lexeme *d = dimension();
    Lexeme *dList = optDimensionList();
    return cons(DIMENSION_LIST, d, dList);
}


Lexeme *optDimensionList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: optDimensionList\n");
    }
    if (dimensionListPending()) {
        return dimensionList();
    }
    return NULL;
}

Lexeme *parameterList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: parameterList\n");
    }
    Lexeme *id = match(ID_TYPE);
    Lexeme *pList = NULL;
    if (check(COMMA)) {
        match(COMMA);
        pList = parameterList();
    }
    return cons(PARAMETER_LIST, id, pList);
}

Lexeme *optParameterList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: optParameterList\n");
    }
    if (parameterListPending()) {
        return parameterList();
    }
    return NULL;
}

Lexeme *variableExpression(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: variableExpression\n");
    }
    Lexeme *id = match(ID_TYPE);
    if (check(OPAREN)) {
        // function call
        match(OPAREN);
        Lexeme *eList = optExpressionList();
        match(CPAREN);
        return cons(FUNCTION_CALL, id, eList);
    }
    else if (dimensionListPending()) {
        // array access
        Lexeme *dList = dimensionList();
        return cons(VARIABLE_EXPRESSION, id, dList);
    }
    else if (binaryOperatorPending()){
        // binary operation
        Lexeme * bop = binaryOperator();
        if (expressionPending()) {
            Lexeme *e = expression();
            return cons(VARIABLE_EXPRESSION, id, cons(JOIN, bop, e));
        }
        else {
            matchNoAdvance("expression");
        }
    }
    else {
        // the variable expression was simply a single ID
        return cons(VARIABLE_EXPRESSION, id, NULL);
    }
    return NULL;
}

Lexeme *expression(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: expression\n");
    }
    if (unaryPending()) {
        Lexeme *u = unary();
        if (binaryOperatorPending()) {
            Lexeme *bop = binaryOperator();
            Lexeme *e = expression();
            return cons(EXPRESSION, u, cons(JOIN, bop, e));
        }
        else if (unaryOperatorPending()) {
            Lexeme *uop = unaryOperator();
            return cons(EXPRESSION, u, uop);
        }
        else if (logicalOperatorPending()) {
            Lexeme *lop = logicalOperator();
            Lexeme *e = expression();
            return cons(EXPRESSION, u, cons(JOIN, lop, e));
        }
        else if (comparatorPending()) {
            Lexeme *c = comparator();
            Lexeme *e = expression();
            return cons(EXPRESSION, u, cons(JOIN, c, e));
        }
        else {
            return cons(EXPRESSION, u, NULL);
        }
    }
    else if (unaryOperatorPending()) {
        // accounts for NEGATE_UNARY operator
        Lexeme *uop = unaryOperator();
        Lexeme *u = unary();
        return cons(EXPRESSION, uop, u);
    }
    else {
        matchNoAdvance("expression");
    }
    return NULL;
}

Lexeme *optExpression(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: optExpression\n");
    }
    if (expressionPending()) {
        return expression();
    }
    return NULL;
}

Lexeme *expressionList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: expressionList\n");
    }
    Lexeme *e = expression();
    if (check(COMMA)) {
        match(COMMA);
        if (expressionListPending()) {
            Lexeme *eList = expressionList();
            return cons(EXPRESSION_LIST, e, eList);
        }
        else {
            matchNoAdvance("expression");
        }
    }
    return cons(EXPRESSION_LIST, e, NULL);
}

Lexeme *optExpressionList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: optExpressionList\n");
    }
    if (expressionListPending()) {
        return expressionList();
    }
    return NULL;
}

Lexeme *conditionalExpressionList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: conditionalExpressionList\n");
    }
    expression();
    if (logicalOperatorPending()) {
        logicalOperator();
        if (conditionalExpressionListPending()) {
            conditionalExpressionList();
        }
        else {
            matchNoAdvance("expression");
        }
    }
}

Lexeme *unary(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: unary\n");
    }
    if (variableExpressionPending()) {
        Lexeme *ve = variableExpression();
        return cons(UNARY, ve, NULL);
    }
    else if (check(INTEGER_TYPE)) {
        Lexeme *i = match(INTEGER_TYPE);
        return cons(UNARY, i, NULL);
    }
    else if (check(REAL_TYPE)) {
        Lexeme *r = match(REAL_TYPE);
        return cons(UNARY, r, NULL);
    }
    else if (check(STRING_TYPE)) {
        Lexeme *s = match(STRING_TYPE);
        return cons(UNARY, s, NULL);
    }
    else if (check(BOOLEAN_TYPE)) {
        Lexeme *b = match(BOOLEAN_TYPE);
        return cons(UNARY, b, NULL);
    }
    else if (check(NEGATE_UNARY)) {
        Lexeme *neg = match(NEGATE_UNARY);
        Lexeme *u = unary();
        return cons(UNARY, neg, u);
    }
    else if (check(NOT)) {
        Lexeme *notOp = match(NOT);
        Lexeme *u = unary();
        return cons(UNARY, notOp, u);
    }
    else if (check(OPAREN)) {
        match(OPAREN);
        Lexeme *e = expression();
        match(CPAREN);
        return cons(UNARY, cons(OPAREN, e, NULL), NULL);
    }
    else if (check(OBRACKET)) {
        match(OBRACKET);
        Lexeme *eList = optExpressionList();
        match(CBRACKET);
        return cons(UNARY, cons(DIMENSION_LIST, eList, NULL), NULL);
    }
    else if (lambdaDefinitionPending()) {
        Lexeme *lamb = lambdaDefinition();
        return cons(UNARY, lamb, NULL);
    }
    else if (check(PRINT)) {
        match(PRINT);
        match(OPAREN);
        Lexeme *eList = expressionList();
        match(CPAREN);
        return cons(UNARY, cons(PRINT, NULL, eList), NULL);
    }
    else if (check(PRINTLN)) {
        match(PRINTLN);
        match(OPAREN);
        Lexeme *eList = expressionList();
        match(CPAREN);
        return cons(UNARY, cons(PRINTLN, NULL, eList), NULL);
    }
    else if (check(NULL_TYPE)) {
        Lexeme *nuhll = match(NULL_TYPE);
        return cons(UNARY, nuhll, NULL);
    }
    return NULL;
}

Lexeme *lambdaDefinition(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: lambdaDefinition\n");
    }
    match(LAMBDA);
    match(OPAREN);
    Lexeme *pList = optParameterList();
    match(CPAREN);
    Lexeme *b = block();
    return cons(LAMBDA_DEFINITION, pList, b);
}

Lexeme *block(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: block\n");
    }
    match(OBRACE);
    Lexeme *sList = optStatementList();
    match(CBRACE);
    return cons(BLOCK, sList, NULL);
}

Lexeme *loop(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: loop\n");
    }
    if (forLoopPending()) {
        forLoop();
    }
    else {
        whileLoop();
    }
}

Lexeme *forLoop(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: forLoop\n");
    }
    match(FOR);
    match(OPAREN);
    if (variableDefinitionPending()) {
        variableDefinition();
    }
    else {
        variableExpression();
    }
    match(SEMICOLON);
    conditionalExpressionList();
    match(SEMICOLON);
    expression();
    match(CPAREN);
    block();
}

Lexeme *whileLoop(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: whileLoop\n");
    }
    match(WHILE);
    match(OPAREN);
    conditionalExpressionList();
    match(CPAREN);
    block();
}

Lexeme *ifStatement(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: ifStatement\n");
    }
    match(IF);
    match(OPAREN);
    conditionalExpressionList();
    match(CPAREN);
    block();
    optElseStatement();
}

Lexeme *elseStatement(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: elseStatement\n");
    }
    match(ELSE);
    if (blockPending()) {
        block();
    }
    else {
        ifStatement();
    }
}

Lexeme *optElseStatement(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: optElseStatement\n");
    }
    if (elseStatementPending()) {
        elseStatement();
    }
}

Lexeme *returnStatement(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: returnStatement\n");
    }
    match(RETURN);
    optExpression();
}

Lexeme *unaryOperator(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: unaryOperator\n");
    }
    Lexeme *op = NULL;
    if (check(NEGATE_UNARY)) {
        op = match(NEGATE_UNARY);
        setLexemeType(op, NEGATE_UNARY);
    }
    else if (check(INCREMENT_UNARY)) {
        op = match(INCREMENT_UNARY);
        setLexemeType(op, INCREMENT_UNARY);
    }
    else if (check(DECREMENT_UNARY)) {
        op = match(DECREMENT_UNARY);
        setLexemeType(op, DECREMENT_UNARY);
    }
    else {
        matchNoAdvance("unary operator");
    }
    return cons(UNARY_OPERATOR, op, NULL);
}

Lexeme *binaryOperator(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: binaryOperator\n");
    }
    Lexeme *op = NULL;
    if (check(PLUS_BINARY)) {
        op = match(PLUS_BINARY);
        setLexemeType(op, PLUS_BINARY);
    }
    else if (check(MINUS_BINARY)) {
        op = match(MINUS_BINARY);
        setLexemeType(op, MINUS_BINARY);
    }
    else if (check(TIMES_BINARY)) {
        op = match(TIMES_BINARY);
        setLexemeType(op, TIMES_BINARY);
    }
    else if (check(DIVIDE_BINARY)) {
        op = match(DIVIDE_BINARY);
        setLexemeType(op, DIVIDE_BINARY);
    }
    else if (check(POW_BINARY)) {
        op = match(POW_BINARY);
        setLexemeType(op, POW_BINARY);
    }
    else if (check(MODULO_BINARY)) {
        op = match(MODULO_BINARY);
        setLexemeType(op, MODULO_BINARY);
    }
    else if (check(ASSIGN_BINARY)) {
        op = match(ASSIGN_BINARY);
        setLexemeType(op, ASSIGN_BINARY);
    }
    else if (check(PLUS_ASSIGN_BINARY)) {
        op = match(PLUS_ASSIGN_BINARY);
        setLexemeType(op, PLUS_ASSIGN_BINARY);
    }
    else if (check(MINUS_ASSIGN_BINARY)) {
        op = match(MINUS_ASSIGN_BINARY);
        setLexemeType(op, MINUS_ASSIGN_BINARY);
    }
    else if (check(TIMES_ASSIGN_BINARY)) {
        op = match(TIMES_ASSIGN_BINARY);
        setLexemeType(op, TIMES_ASSIGN_BINARY);
    }
    else if (check(DIVIDE_ASSIGN_BINARY)) {
        op = match(DIVIDE_ASSIGN_BINARY);
        setLexemeType(op, DIVIDE_ASSIGN_BINARY);
    }
    else if (check(POW_ASSIGN_BINARY)) {
        op = match(POW_ASSIGN_BINARY);
        setLexemeType(op, POW_ASSIGN_BINARY);
    }
    else if (check(MODULO_ASSIGN_BINARY)) {
        op = match(MODULO_ASSIGN_BINARY);
        setLexemeType(op, MODULO_ASSIGN_BINARY);
    }
    else if (check(DOT_BINARY)) {
        op = match(DOT_BINARY);
        setLexemeType(op, DOT_BINARY);
    }
    else {
        matchNoAdvance("binary operator");
    }
    return cons(BINARY_OPERATOR, op, NULL);
}

Lexeme *logicalOperator(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: logicalOperator\n");
    }
    Lexeme *op = NULL;
    if (check(AND)) {
        op = match(AND);
        setLexemeType(op, AND);
    }
    else if (check(OR)) {
        op = match(OR);
        setLexemeType(op, OR);
    }
    else if (check(XOR)) {
        op = match(XOR);
        setLexemeType(op, XOR);
    }
    else {
        matchNoAdvance("logical operator");
    }
    return cons(LOGICAL_OPERATOR, op, NULL);
}

Lexeme *comparator(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: comparator\n");
    }
    Lexeme *comp = NULL;
    if (check(EQUALS_COMPARATOR)) {
        comp = match(EQUALS_COMPARATOR);
        setLexemeType(comp, EQUALS_COMPARATOR);
    }
    else if (check(NOT_EQUALS_COMPARATOR)) {
        comp = match(NOT_EQUALS_COMPARATOR);
        setLexemeType(comp, NOT_EQUALS_COMPARATOR);
    }
    else if (check(GREATER_THAN_COMPARATOR)) {
        comp = match(GREATER_THAN_COMPARATOR);
        setLexemeType(comp, GREATER_THAN_COMPARATOR);
    }
    else if (check(LESSER_THAN_COMPARATOR)) {
        comp = match(LESSER_THAN_COMPARATOR);
        setLexemeType(comp, LESSER_THAN_COMPARATOR);
    }
    else if (check(GREATER_EQUALS_COMPARATOR)) {
        comp = match(GREATER_EQUALS_COMPARATOR);
        setLexemeType(comp, GREATER_EQUALS_COMPARATOR);
    }
    else if (check(LESSER_EQUALS_COMPARATOR)) {
        comp = match(LESSER_EQUALS_COMPARATOR);
        setLexemeType(comp, LESSER_EQUALS_COMPARATOR);
    }
    else {
        matchNoAdvance("comparator");
    }
    return cons(COMPARATOR, comp, NULL);
}


/********** Predicate Function Definitions **********/

bool programPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: programPending\n");
    }
    return importPending() || statementListPending();
}

bool importPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: importPending\n");
    }
    return check(IMPORT);
}

bool statementPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: statementPending\n");
    }
    return definitionPending() || expressionPending() || loopPending()
        || ifStatementPending() || returnStatementPending() || check(CONTINUE)
        || check(BREAK);
}

bool statementListPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: statementListPending\n");
    }
    return statementPending();
}

bool definitionPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: definitionPending\n");
    }
    return variableDefinitionPending() || functionDefinitionPending()
        || classDefinitionPending();
}

bool variableDefinitionPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: variableDefinitionPending\n");
    }
    return check(VAR);
}

bool functionDefinitionPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: functionDefinitionPending\n");
    }
    return check(FUNCTION);
}

bool classDefinitionPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: classDefinitionPending\n");
    }
    return check(CLASS);
}

bool dimensionPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: dimensionPending\n");
    }
    return check(OBRACKET);
}

bool dimensionListPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: dimensionListPending\n");
    }
    return dimensionPending();
}

bool parameterListPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: parameterListPending\n");
    }
    return check(ID_TYPE);
}

bool variableExpressionPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: variableExpressionPending\n");
    }
    return check(ID_TYPE);
}

bool expressionPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: expressionPending\n");
    }
    return unaryPending() || unaryOperatorPending();
}

bool expressionListPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: expressionListPending\n");
    }
    return expressionPending();
}

bool conditionalExpressionListPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: conditionalExpressionListPending\n");
    }
    return expressionPending();
}

bool unaryPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: unaryPending\n");
    }
    return variableExpressionPending() || check(INTEGER_TYPE)
        || check(REAL_TYPE) || check(STRING_TYPE) || check(BOOLEAN_TYPE)
        || check(MINUS_BINARY) || check(NOT) || check(OPAREN) || check(OBRACKET) || lambdaDefinitionPending()
        || check(PRINT) || check(PRINTLN) || check(NULL_TYPE);
}

bool lambdaDefinitionPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: lambdaDefinitionPending\n");
    }
    return check(LAMBDA);
}

bool blockPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: blockPending\n");
    }
    return check(OBRACE);
}

bool loopPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: loopPending\n");
    }
    return forLoopPending() || whileLoopPending();
}

bool forLoopPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: forLoopPending\n");
    }
    return check(FOR);
}

bool whileLoopPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: whileLoopPending\n");
    }
    return check(WHILE);
}

bool ifStatementPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: ifStatementPending\n");
    }
    return check(IF);
}

bool elseStatementPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: elseStatementPending\n");
    }
    return check(ELSE);
}

bool returnStatementPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: returnStatementPending\n");
    }
    return check(RETURN);
}

bool unaryOperatorPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: unaryOperatorPending\n");
    }
    return check(NEGATE_UNARY) || check(INCREMENT_UNARY)
        || check(DECREMENT_UNARY);
}

bool binaryOperatorPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: binaryOperatorPending\n");
    }
    return check(PLUS_BINARY) || check(MINUS_BINARY) || check(TIMES_BINARY)
        || check(DIVIDE_BINARY) || check(POW_BINARY) || check(MODULO_BINARY)
        || check(ASSIGN_BINARY) || check(PLUS_ASSIGN_BINARY)
        || check(MINUS_ASSIGN_BINARY) || check(TIMES_ASSIGN_BINARY)
        || check(DIVIDE_ASSIGN_BINARY) || check(POW_ASSIGN_BINARY)
        || check(MODULO_ASSIGN_BINARY) || check(DOT_BINARY);
}

bool logicalOperatorPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: logicalOperatorPending\n");
    }
    return check(AND) || check(OR) || check(XOR);
}

bool comparatorPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: comparatorPending\n");
    }
    return check(LESSER_THAN_COMPARATOR) || check(GREATER_THAN_COMPARATOR)
        || check(LESSER_EQUALS_COMPARATOR) || check(GREATER_EQUALS_COMPARATOR)
        || check(EQUALS_COMPARATOR) || check(NOT_EQUALS_COMPARATOR);
}
