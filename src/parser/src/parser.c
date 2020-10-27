/*
 *  Author:         Brett Heithold
 *  File:           parser.c
 *  Created on:     10/25/2020
 *  Last revision:  10/27/2020
 */


#include "../header/parser.h"
#include "../../Lexer/header/lexeme.h"
#include "../../Lexer/header/lexer.h"
#include "../../Lexer/header/types.h"

#include <assert.h>
#include <stdlib.h>


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
    advance();
    return currentLexeme;
}

void matchNoAdvance(char *type) {
    assert(type != NULL);
    assert(currentLexeme != NULL);
    if (!check(type)) {
        fprintf(stdout, "ERROR, line %d: ", getLexemeLineNumber(currentLexeme));
        fprintf(stdout, "expected %s, but encountered %s\n", type, getLexemeType(currentLexeme));
        exit(1);
    }
}


/********** Grammar Function Definitions **********/

void program(void) {
    if (importPending()) {
        import();
        if (programPending()) {
            program();
        }
    }
    else if (statementListPending()) {
        statementList();
        if (programPending()) {
            program();
        }
    }
}

void import(void) {
    match(IMPORT);
    match(STRING_TYPE);
}

void statement(void) {
    if (definitionPending()) {
        definition();
    }
    else if (expressionPending()) {
        expression();
    }
    else if (loopPending()) {
        loop();
    }
    else if (ifStatementPending()) {
        ifStatement();
    }
    else if (returnStatementPending()) {
        returnStatement();
    }
    else if (check(CONTINUE)) {
        match(CONTINUE);
        match(SEMICOLON);
    }
    else if (check(BREAK)) {
        match(BREAK);
        match(SEMICOLON);
    }
}

void statementList(void) {
    if (statementPending()) {
        statement();
        optStatementList();
    }
}

void optStatementList(void) {
    if (statementListPending()) {
        statementList();
    }
}

void definition(void) {
    if (variableDefinitionPending()) {
        variableDefinition();
    }
    else if (functionDefinitionPending()) {
        functionDefinition();
    }
    else if (classDefinitionPending()) {
        classDefinition();
    }
}

void variableDefinition(void) {
    if (check(VARIABLE_TYPE)) {
        match(VARIABLE_TYPE);
        match(ID_TYPE);
        optInit();
        match(SEMICOLON);
    }
    else {
        match(ID_TYPE);
        match(ASSIGN_BINARY);
        expression();
    }
}

void optInit(void) {
    if (check(ASSIGN_BINARY)) {
        match(ASSIGN_BINARY);
        expression();
    }
}

void variableExpression(void) {
    match(ID_TYPE);
    if (check(OPAREN)) {
        match(OPAREN);
        optExpressionList();
        match(CPAREN);
    }
    else {
        match(OBRACKET);
        optExpressionList();
        match(CBRACKET);
    }
}

void functionDefinition(void) {
    match(FUNCTION);
    match(ID_TYPE);
    match(OPAREN);
    if (parameterListPending()) {
        parameterList();
        match(CPAREN);
        block();
    }
    else {
        match(VOID);
        match(CPAREN);
        block();
    }
}

void classDefinition(void) {
    match(CLASS);
    match(ID_TYPE);
    optInheritance();
    block();
}

void optInheritance(void) {
    if (check(COLON)) {
        match(COLON);
        match(ID_TYPE);
    }
}

void parameterList(void) {
    match(ID_TYPE);
    if (check(COMMA)) {
        match(COMMA);
        parameterList();
    }
}

void optParameterList(void) {
    if (parameterListPending()) {
        parameterList();
    }
}

void expression(void) {
    if (unaryPending()) {
        unary();
        if (binaryOperatorPending()) {
            binaryOperator();
            expression();
        }
        else if (unaryOperatorPending()) {
            unaryOperator();
        }
    }
    else {
        unaryOperator();
        unary();
    }
}

void optExpression(void) {
    if (expressionPending()) {
        expression();
    }
}

void expressionList(void) {
    expression();
    if (check(COMMA)) {
        match(COMMA);
        expressionList();
    }
}

void optExpressionList(void) {
    if (expressionListPending()) {
        expressionList();
    }
}

void unary(void) {
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
        expression();
        match(CPAREN);
    }
    else if (lambdaDefinitionPending()) {
        lambdaDef();
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

void lambdaDefinition(void) {
    match(LAMBDA);
    match(OPAREN);
    optParameterList();
    match(CPAREN);
    block();
}


/********** Predicate Function Definitions **********/

bool programPending(void) {
    return importPending() || statementListPending();
}

bool importPending(void) {
    return check(IMPORT);
}

bool statementPending(void) {
    return definitionPending() || expressionPending() || loopPending()
        || ifStatementPending() || returnStatementPending() || check(CONTINUE)
        || check(BREAK);
}

bool statementListPending(void) {
    return statementPending();
}

bool definitionPending(void) {
    return variableDefinitionPending() || functionDefinitionPending()
        || classDefinitionPending();
}

bool variableDefinitionPending(void) {
    return check(VAR) || check(ID_TYPE);
}

bool variableExpressionPending(void) {
    return check(ID_TYPE);
}

bool functionDefinitionPending(void) {
    return check(FUNCTION);
}

bool classDefinitionPending(void) {
    return check(CLASS);
}

bool parameterListPending(void) {
    return check(ID_TYPE);
}

bool expressionPending(void) {
    return unaryPending() || unaryOperatorPending();
}

bool expressionListPending(void) {
    return expressionPending();
}

bool unaryPending(void) {
    return variableExpressionPending() || check(INTEGER_TYPE)
        || check(REAL_TYPE) || check(STRING_TYPE) || check(BOOLEAN_TYPE)
        || check(MINUS_BINARY) || check(OPAREN) || lambdaDefinitionPending()
        || check(PRINT) || check(PRINTLN) || check(NULL_TYPE);
}

bool lambdaDefinitionPending(void) {
    return check(LAMBDA);
}

bool blockPending(void) {
    return check(OBRACE);
}

bool loopPending(void) {
    return forLoopPending() || whileLoopPending();
}

bool forLoopPending(void) {
    return check(FOR);
}

bool whileLoopPending(void) {
    return check(WHILE);
}

bool ifStatementPending(void) {
    return check(IF);
}

bool returnStatementPending(void) {
    return check(RETURN);
}

bool elseStatementPending(void) {
    return check(ELSE);
}

bool unaryOperatorPending(void) {
    return check(NEGATE_UNARY) || check(INCREMENT_UNARY)
        || check(DECREMENT_UNARY);
}

bool binaryOperatorPending(void) {
    return check(PLUS_BINARY) || check(MINUS_BINARY) || check(TIMES_BINARY)
        || check(DIVIDE_BINARY) || check(POW_BINARY) || check(MODULO_BINARY)
        || check(ASSIGN_BINARY) || check(PLUS_ASSIGN_BINARY)
        || check(MINUS_ASSIGN_BINARY) || check(TIMES_ASSIGN_BINARY)
        || check(DIVIDE_ASSIGN_BINARY) || check(POW_ASSIGN_BINARY)
        || check(MODULO_ASSIGN_BINARY) || check(DOT_BINARY);
}

bool logicalOperatorPending(void) {
    return check(AND) || check(OR) || check(XOR);
}

bool comparatorPending(void) {
    return check(LESSER_THAN_COMPARATOR) || check(GREATER_THAN_COMPARATOR)
        || check(LESSER_EQUALS_COMPARATOR) || check(GREATER_EQUALS_COMPARATOR)
        || check(EQUALS_COMPARATOR) || check(NOT_EQUALS_COMPARATOR);
}
