/*
 *  Author:         Brett Heithold
 *  File:           environment.h
 *  Created on:     10/31/2020
 *  Last revision:  10/31/2020
 */

#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__


#include "../../lexer/lexeme.h"

#include <stdio.h>


Lexeme *createEnvironment(void);
Lexeme *lookupEnvironment(Lexeme *, Lexeme *);
Lexeme *updateEnvironment(Lexeme *, Lexeme *, Lexeme *);
Lexeme *insertEnvironment(Lexeme *, Lexeme *, Lexeme *);
Lexeme *extendEnvironment(Lexeme *, Lexeme *, Lexeme *);
void    printEnvironment(FILE *, Lexeme *);


#endif // !__ENVIRONMENT_H__
