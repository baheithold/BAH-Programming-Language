/*
 *  Author:         Brett Heithold
 *  File:           lexer.h
 *  Created:        10/21/2020
 *  Last Revised:   10/25/2020
 */

#ifndef __LEXER_H__
#define __LEXER_H__


#include "lexeme.h"

#include <stdio.h>


extern void      initLexer(FILE *);
extern Lexeme   *lex(void);
extern int       getLexerLineNumber(void);


#endif // !__LEXER_H__
