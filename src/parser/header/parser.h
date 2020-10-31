/*
 *  Author:         Brett Heithold
 *  File:           parser.h
 *  Created on:     10/25/2020
 *  Last revision:  10/30/2020
 */

#ifndef __PARSER_H__
#define __PARSER_H__


#include "../../lexer/header/lexeme.h"

#include <stdbool.h>


/********** Lexer Interface Function Prototypes **********/
extern bool      check(char *);
extern void      advance(void);
extern Lexeme   *match(char *);
extern void      matchNoAdvance(char *);


/********** Grammar Function Prototypes **********/
extern void program(void);
extern void import(void);
extern void statement(void);
extern void statementList(void);
extern void optStatementList(void);
extern void definition(void);
extern void variableDefinition(void);
extern void functionDefinition(void);
extern void classDefinition(void);
extern void optInheritance(void);
extern void optInit(void);
extern void dimension(void);
extern void dimensionList(void);
extern void optDimensionList(void);
extern void parameterList(void);
extern void optParameterList(void);
extern void variableExpression(void);
extern void expression(void);
extern void optExpression(void);
extern void expressionList(void);
extern void optExpressionList(void);
extern void unary(void);
extern void lambdaDefinition(void);
extern void block(void);
extern void loop(void);
extern void forLoop(void);
extern void whileLoop(void);
extern void ifStatement(void);
extern void elseStatement(void);
extern void optElseStatement(void);
extern void returnStatement(void);
extern void unaryOperator(void);
extern void binaryOperator(void);
extern void logicalOperator(void);
extern void comparator(void);


/********** Predicate Function Prototypes **********/
extern bool programPending(void);
extern bool importPending(void);
extern bool statementPending(void);
extern bool statementListPending(void);
extern bool definitionPending(void);
extern bool variableDefinitionPending(void);
extern bool functionDefinitionPending(void);
extern bool classDefinitionPending(void);
extern bool dimensionPending(void);
extern bool dimensionListPending(void);
extern bool parameterListPending(void);
extern bool variableExpressionPending(void);
extern bool expressionPending(void);
extern bool expressionListPending(void);
extern bool conditionalExpressionListPending(void);
extern bool unaryPending(void);
extern bool lambdaDefinitionPending(void);
extern bool blockPending(void);
extern bool loopPending(void);
extern bool forLoopPending(void);
extern bool whileLoopPending(void);
extern bool ifStatementPending(void);
extern bool elseStatementPending(void);
extern bool returnStatementPending(void);
extern bool unaryOperatorPending(void);
extern bool binaryOperatorPending(void);
extern bool logicalOperatorPending(void);
extern bool comparatorPending(void);


#endif // !__PARSER_H__
