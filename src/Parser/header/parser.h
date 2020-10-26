/*
 *  Author:         Brett Heithold
 *  File:           parser.h
 *  Created on:     10/25/2020
 *  Last revision:  10/25/2020
 */

#ifndef __PARSER_H__
#define __PARSER_H__


#include "Lexeme.h"


extern void      advance(void);
extern Lexeme   *match(void);
extern void      matchNoAdvance(char *);
extern int       check(char *);


#endif // !__PARSER_H__
