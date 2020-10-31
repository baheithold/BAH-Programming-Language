/*
 *  Author:         Brett Heithold
 *  File:           lexeme.h
 *  Created:        10/21/2020
 *  Last Revised:   10/31/2020
 */

#ifndef __LEXEME_H__
#define __LEXEME_H__


#include <stdio.h>


typedef struct Lexeme Lexeme;

extern Lexeme   *newLexeme(char *, char *);
extern char     *getLexemeType(Lexeme *);
extern void      setLexemeType(Lexeme *, char *);
extern int       getLexemeIntegerValue(Lexeme *);
extern double    getLexemeRealValue(Lexeme *);
extern char     *getLexemeStringValue(Lexeme *);
extern void      setLexemeValue(Lexeme *, char *);
extern int       getLexemeLineNumber(Lexeme *);
extern void      setLexemeLineNumber(Lexeme *, int);
extern Lexeme   *getLexemeLeftChild(Lexeme *);
extern void      setLexemeLeftChild(Lexeme *, Lexeme *);
extern Lexeme   *getLexemeRightChild(Lexeme *);
extern void      setLexemeRightChild(Lexeme *, Lexeme *);
extern void      printLexeme(FILE *, Lexeme *);

#endif // !__LEXEME_H__
