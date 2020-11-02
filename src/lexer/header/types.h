/*
 *  Author:         Brett Heithold
 *  File:           types.h
 *  Created:        10/21/2020
 *  Last Revised:   11/1/2020
 */

#ifndef __TYPES_H__
#define __TYPES_H__


/* Types */
extern char *INTEGER_TYPE;
extern char *REAL_TYPE;
extern char *STRING_TYPE;
extern char *BOOLEAN_TYPE;
extern char *ID_TYPE;
extern char *VARIABLE_TYPE;
extern char *NULL_TYPE;

/* Punctuation */
extern char *OPAREN;
extern char *CPAREN;
extern char *OBRACE;
extern char *CBRACE;
extern char *OBRACKET;
extern char *CBRACKET;
extern char *COMMA;
extern char *COLON;
extern char *SEMICOLON;

/* Binary Operators */
extern char *PLUS_BINARY;
extern char *MINUS_BINARY;
extern char *TIMES_BINARY;
extern char *DIVIDE_BINARY;
extern char *POW_BINARY;
extern char *MODULO_BINARY;
extern char *ASSIGN_BINARY;
extern char *PLUS_ASSIGN_BINARY;
extern char *MINUS_ASSIGN_BINARY;
extern char *TIMES_ASSIGN_BINARY;
extern char *DIVIDE_ASSIGN_BINARY;
extern char *POW_ASSIGN_BINARY;
extern char *MODULO_ASSIGN_BINARY;
extern char *DOT_BINARY;

/* Unary Operators */
extern char *INCREMENT_UNARY;
extern char *DECREMENT_UNARY;
extern char *NEGATE_UNARY;

/* Comparators */
extern char *EQUALS_COMPARATOR;
extern char *NOT_EQUALS_COMPARATOR;
extern char *GREATER_THAN_COMPARATOR;
extern char *LESSER_THAN_COMPARATOR;
extern char *GREATER_EQUALS_COMPARATOR;
extern char *LESSER_EQUALS_COMPARATOR;

/* Logical Operators */
extern char *AND;
extern char *OR;
extern char *XOR;

/* Keywords */
extern char *IF;
extern char *ELSE;
extern char *FOR;
extern char *WHILE;
extern char *FUNCTION;
extern char *VAR;
extern char *RETURN;
extern char *BREAK;
extern char *CONTINUE;
extern char *CLASS;
extern char *LAMBDA;
extern char *VOID;
extern char *IMPORT;
extern char *PRINT;
extern char *PRINTLN;

/* Other */
extern char *UNKNOWN;
extern char *BAD_NUMBER;
extern char *BAD_CHARACTER;
extern char *BAD_STRING;
extern char *END_OF_INPUT;
extern char *VARIABLE_DEFINITION;
extern char *FUNCTION_DEFINITION;
extern char *FUNCTION_CALL;
extern char *CLASS_DEFINITION;
extern char *ENVIRONMENT;
extern char *JOIN;


#endif // !__TYPES_H__
