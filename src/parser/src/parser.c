/*
 *  Author:         Brett Heithold
 *  File:           parser.c
 *  Created on:     10/25/2020
 *  Last revision:  11/13/2020
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
        return definition();
    }
    else if (expressionPending()) {
        return expression();
        match(SEMICOLON);
    }
    else if (loopPending()) {
        return loop();
    }
    else if (ifStatementPending()) {
        return ifStatement();
    }
    else if (returnStatementPending()) {
        return returnStatement();
        match(SEMICOLON);
    }
    else if (check(CONTINUE)) {
        return match(CONTINUE);
        match(SEMICOLON);
    }
    else if (check(BREAK)) {
        return match(BREAK);
        match(SEMICOLON);
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
    if (parameterListPending()) {
        Lexeme *pList = parameterList();
        match(CPAREN);
        Lexeme *b = block();
        return cons(FUNCTION_DEFINITION, id, cons(JOIN, pList, b));
    }
    else {
        match(VOID);
        match(CPAREN);
        block();
    }
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
            expression();
        }
        else {
            matchNoAdvance("expression");
        }
    }
}

Lexeme *dimension(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: dimension\n");
    }
    match(OBRACKET);
    optExpressionList();
    match(CBRACKET);
}


Lexeme *dimensionList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: dimensionList\n");
    }
    dimension();
    optDimensionList();
}

Lexeme *optDimensionList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: optDimensionList\n");
    }
    if (dimensionListPending()) {
        dimensionList();
    }
}

Lexeme *parameterList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: parameterList\n");
    }
    match(ID_TYPE);
    if (check(COMMA)) {
        match(COMMA);
        parameterList();
    }
}

Lexeme *optParameterList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: optParameterList\n");
    }
    if (parameterListPending()) {
        parameterList();
    }
}

Lexeme *variableExpression(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: variableExpression\n");
    }
    match(ID_TYPE);
    if (check(OPAREN)) {
        match(OPAREN);
        optExpressionList();
        match(CPAREN);
    }
    else if (dimensionListPending()) {
        dimensionList();
    }
    else if (binaryOperatorPending()){
        binaryOperator();
        if (expressionPending()) {
            expression();
        }
        else {
            matchNoAdvance("expression");
        }
    }
}

Lexeme *expression(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: expression\n");
    }
    if (unaryPending()) {
        unary();
        if (binaryOperatorPending()) {
            binaryOperator();
            expression();
        }
        else if (unaryOperatorPending()) {
            unaryOperator();
        }
        else if (logicalOperatorPending()) {
            logicalOperator();
            expression();
        }
        else if (comparatorPending()) {
            comparator();
            expression();
        }
    }
    else if (unaryOperatorPending()) {
        // accounts for NEGATE_UNARY operator
        unaryOperator();
        unary();
    }
    else {
        matchNoAdvance("expression");
    }
}

Lexeme *optExpression(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: optExpression\n");
    }
    if (expressionPending()) {
        expression();
    }
}

Lexeme *expressionList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: expressionList\n");
    }
    expression();
    if (check(COMMA)) {
        match(COMMA);
        if (expressionListPending()) {
            expressionList();
        }
        else {
            matchNoAdvance("expression");
        }
    }
}

Lexeme *optExpressionList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: optExpressionList\n");
    }
    if (expressionListPending()) {
        expressionList();
    }
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
        variableExpression();
    }
    else if (check(INTEGER_TYPE)) {
        match(INTEGER_TYPE);
    }
    else if (check(REAL_TYPE)) {
        match(REAL_TYPE);
    }
    else if (check(STRING_TYPE)) {
        match(STRING_TYPE);
    }
    else if (check(BOOLEAN_TYPE)) {
        match(BOOLEAN_TYPE);
    }
    else if (check(NEGATE_UNARY)) {
        match(NEGATE_UNARY);
        unary();
    }
    else if (check(OPAREN)) {
        match(OPAREN);
        expression();
        match(CPAREN);
    }
    else if (check(OBRACKET)) {
        match(OBRACKET);
        optExpressionList();
        match(CBRACKET);
    }
    else if (lambdaDefinitionPending()) {
        lambdaDefinition();
    }
    else if (check(PRINT)) {
        match(PRINT);
        match(OPAREN);
        expressionList();
        match(CPAREN);
    }
    else if (check(PRINTLN)) {
        match(PRINTLN);
        match(OPAREN);
        expressionList();
        match(CPAREN);
    }
    else if (check(NULL_TYPE)) {
        match(NULL_TYPE);
    }
}

Lexeme *lambdaDefinition(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: lambdaDefinition\n");
    }
    match(LAMBDA);
    match(OPAREN);
    optParameterList();
    match(CPAREN);
    block();
}

Lexeme *block(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: block\n");
    }
    match(OBRACE);
    optStatementList();
    match(CBRACE);
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
    if (check(NEGATE_UNARY)) {
        match(NEGATE_UNARY);
    }
    else if (check(INCREMENT_UNARY)) {
        match(INCREMENT_UNARY);
    }
    else if (check(DECREMENT_UNARY)) {
        match(DECREMENT_UNARY);
    }
}

Lexeme *binaryOperator(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: binaryOperator\n");
    }
    if (check(PLUS_BINARY)) {
        match(PLUS_BINARY);
    }
    else if (check(MINUS_BINARY)) {
        match(MINUS_BINARY);
    }
    else if (check(TIMES_BINARY)) {
        match(TIMES_BINARY);
    }
    else if (check(DIVIDE_BINARY)) {
        match(DIVIDE_BINARY);
    }
    else if (check(POW_BINARY)) {
        match(POW_BINARY);
    }
    else if (check(MODULO_BINARY)) {
        match(MODULO_BINARY);
    }
    else if (check(ASSIGN_BINARY)) {
        match(ASSIGN_BINARY);
    }
    else if (check(PLUS_ASSIGN_BINARY)) {
        match(PLUS_ASSIGN_BINARY);
    }
    else if (check(MINUS_ASSIGN_BINARY)) {
        match(MINUS_ASSIGN_BINARY);
    }
    else if (check(TIMES_ASSIGN_BINARY)) {
        match(TIMES_ASSIGN_BINARY);
    }
    else if (check(DIVIDE_ASSIGN_BINARY)) {
        match(DIVIDE_ASSIGN_BINARY);
    }
    else if (check(POW_ASSIGN_BINARY)) {
        match(POW_ASSIGN_BINARY);
    }
    else if (check(MODULO_ASSIGN_BINARY)) {
        match(MODULO_ASSIGN_BINARY);
    }
    else if (check(DOT_BINARY)) {
        match(DOT_BINARY);
    }
}

Lexeme *logicalOperator(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: logicalOperator\n");
    }
    if (check(AND)) {
        match(AND);
    }
    else if (check(OR)) {
        match(OR);
    }
    else {
        match(XOR);
    }
}

Lexeme *comparator(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: comparator\n");
    }
    if (check(EQUALS_COMPARATOR)) {
        match(EQUALS_COMPARATOR);
    }
    else if (check(NOT_EQUALS_COMPARATOR)) {
        match(NOT_EQUALS_COMPARATOR);
    }
    else if (check(GREATER_THAN_COMPARATOR)) {
        match(GREATER_THAN_COMPARATOR);
    }
    else if (check(LESSER_THAN_COMPARATOR)) {
        match(LESSER_THAN_COMPARATOR);
    }
    else if (check(GREATER_EQUALS_COMPARATOR)) {
        match(GREATER_EQUALS_COMPARATOR);
    }
    else if (check(LESSER_EQUALS_COMPARATOR)) {
        match(LESSER_EQUALS_COMPARATOR);
    }
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
        || check(MINUS_BINARY) || check(OPAREN) || check(OBRACKET) || lambdaDefinitionPending()
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
