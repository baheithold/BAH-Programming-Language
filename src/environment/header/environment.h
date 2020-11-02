/*
 *  Author:         Brett Heithold
 *  File:           environment.h
 *  Created on:     10/31/2020
 *  Last revision:  11/1/2020
 */

#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__


#include "../../lexer/header/lexeme.h"

#include <stdbool.h>
#include <stdio.h>


extern Lexeme *createEnvironment(void);
extern Lexeme *lookupEnvironment(Lexeme *, Lexeme *);
extern Lexeme *updateEnvironment(Lexeme *, Lexeme *, Lexeme *);
extern Lexeme *insertEnvironment(Lexeme *, Lexeme *, Lexeme *);
extern Lexeme *extendEnvironment(Lexeme *, Lexeme *, Lexeme *);
extern void    printEnvironment(FILE *, Lexeme *, bool);


#endif // !__ENVIRONMENT_H__
