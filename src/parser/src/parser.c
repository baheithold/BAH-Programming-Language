/*
 *  Author:         Brett Heithold
 *  File:           parser.c
 *  Created on:     10/25/2020
 *  Last revision:  10/28/2020
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
    advance();
    return currentLexeme;
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

void program(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: program\n");
    }
    if (importPending()) {
        import();
        program();
    }
    else if (statementListPending()) {
        statementList();
    }
}

void import(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: import\n");
    }
    match(IMPORT);
    match(STRING_TYPE);
}

void statement(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: statement\n");
    }
    if (definitionPending()) {
        definition();
    }
    else if (expressionPending()) {
        expression();
        match(SEMICOLON);
    }
    else if (loopPending()) {
        loop();
    }
    else if (ifStatementPending()) {
        ifStatement();
    }
    else if (returnStatementPending()) {
        returnStatement();
        match(SEMICOLON);
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
    if (DEBUG) {
        fprintf(stdout, "CALL: statementList\n");
    }
    if (statementPending()) {
        statement();
        optStatementList();
    }
}

void optStatementList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: optStatementList\n");
    }
    if (statementListPending()) {
        statementList();
    }
}

void definition(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: definition\n");
    }
    if (variableDefinitionPending()) {
        variableDefinition();
        match(SEMICOLON);
    }
    else if (functionDefinitionPending()) {
        functionDefinition();
    }
    else if (classDefinitionPending()) {
        classDefinition();
    }
}

void variableDefinition(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: variableDefinition\n");
    }
    match(VAR);
    match(ID_TYPE);
    optInit();
}

void optInit(void) {
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

void variableExpression(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: variableExpression\n");
    }
    match(ID_TYPE);
    if (check(OPAREN)) {
        match(OPAREN);
        optExpressionList();
        match(CPAREN);
    }
    else if (check(OBRACKET)) {
        match(OBRACKET);
        optExpressionList();
        match(CBRACKET);
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

void functionDefinition(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: functionDefinition\n");
    }
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
    if (DEBUG) {
        fprintf(stdout, "CALL: classDefinition\n");
    }
    match(CLASS);
    match(ID_TYPE);
    optInheritance();
    block();
}

void optInheritance(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: oprtInheritance\n");
    }
    if (check(COLON)) {
        match(COLON);
        match(ID_TYPE);
    }
}

void parameterList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: parameterList\n");
    }
    match(ID_TYPE);
    if (check(COMMA)) {
        match(COMMA);
        parameterList();
    }
}

void optParameterList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: optParameterList\n");
    }
    if (parameterListPending()) {
        parameterList();
    }
}

void expression(void) {
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

void optExpression(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: optExpression\n");
    }
    if (expressionPending()) {
        expression();
    }
}

void expressionList(void) {
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

void optExpressionList(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: optExpressionList\n");
    }
    if (expressionListPending()) {
        expressionList();
    }
}

void conditionalExpressionList(void) {
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

void unary(void) {
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

void lambdaDefinition(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: lambdaDefinition\n");
    }
    match(LAMBDA);
    match(OPAREN);
    optParameterList();
    match(CPAREN);
    block();
}

void block(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: block\n");
    }
    match(OBRACE);
    optStatementList();
    match(CBRACE);
}

void loop(void) {
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

void forLoop(void) {
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

void whileLoop(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: whileLoop\n");
    }
    match(WHILE);
    match(OPAREN);
    conditionalExpressionList();
    match(CPAREN);
    block();
}

void ifStatement(void) {
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

void elseStatement(void) {
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

void optElseStatement(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: optElseStatement\n");
    }
    if (elseStatementPending()) {
        elseStatement();
    }
}

void returnStatement(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: returnStatement\n");
    }
    match(RETURN);
    optExpression();
}

void unaryOperator(void) {
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

void binaryOperator(void) {
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

void logicalOperator(void) {
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

void comparator(void) {
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

bool variableExpressionPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: variableExpressionPending\n");
    }
    return check(ID_TYPE);
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

bool parameterListPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: parameterListPending\n");
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

bool returnStatementPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: returnStatementPending\n");
    }
    return check(RETURN);
}

bool elseStatementPending(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: elseStatementPending\n");
    }
    return check(ELSE);
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
