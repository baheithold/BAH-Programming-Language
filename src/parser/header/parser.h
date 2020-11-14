/*
 *  Author:         Brett Heithold
 *  File:           parser.h
 *  Created on:     10/25/2020
 *  Last revision:  10/31/2020
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
extern Lexeme *program(void);
extern Lexeme *import(void);
extern Lexeme *statement(void);
extern Lexeme *statementList(void);
extern Lexeme *optStatementList(void);
extern Lexeme *definition(void);
extern Lexeme *variableDefinition(void);
extern Lexeme *functionDefinition(void);
extern Lexeme *classDefinition(void);
extern Lexeme *optInheritance(void);
extern Lexeme *optInit(void);
extern Lexeme *dimension(void);
extern Lexeme *dimensionList(void);
extern Lexeme *optDimensionList(void);
extern Lexeme *parameterList(void);
extern Lexeme *optParameterList(void);
extern Lexeme *variableExpression(void);
extern Lexeme *expression(void);
extern Lexeme *optExpression(void);
extern Lexeme *expressionList(void);
extern Lexeme *optExpressionList(void);
extern Lexeme *unary(void);
extern Lexeme *lambdaDefinition(void);
extern Lexeme *block(void);
extern Lexeme *loop(void);
extern Lexeme *forLoop(void);
extern Lexeme *whileLoop(void);
extern Lexeme *ifStatement(void);
extern Lexeme *elseStatement(void);
extern Lexeme *optElseStatement(void);
extern Lexeme *returnStatement(void);
extern Lexeme *unaryOperator(void);
extern Lexeme *binaryOperator(void);
extern Lexeme *logicalOperator(void);
extern Lexeme *comparator(void);


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
