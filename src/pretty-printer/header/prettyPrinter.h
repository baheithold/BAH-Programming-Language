/*
 *  Author:         Brett Heithold
 *  File:           prettyPrinter.h
 *  Created on:     11/10/2020
 *  Last revision:  11/10/2020
 */

#ifndef __PRETTYPRINTER_H__
#define __PRETTYPRINTER_H__


#include "../../lexer/header/lexeme.h"

#include <stdio.h>


void prettyPrint(FILE *, Lexeme *);


#endif // !__PRETTYPRINTER_H__
