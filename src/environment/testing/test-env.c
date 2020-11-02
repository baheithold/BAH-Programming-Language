/*
 *  Author:         Brett Heithold
 *  File:           test-env.c
 *  Created on:     10/31/2020
 *  Last revision:  11/2/2020
 */


#include "../header/environment.h"
#include "../../lexer/header/lexeme.h"
#include "../../lexer/header/types.h"


int main(void) {
    // Create environment
    Lexeme *global = createEnvironment();
    printf("Creating new environment...\n");


    // Inserting variables into the global scope
    Lexeme *x = newLexeme(ID_TYPE, "x");
    Lexeme *one = newLexeme(INTEGER_TYPE, "1");
    Lexeme *y = newLexeme(ID_TYPE, "y");
    Lexeme *two = newLexeme(INTEGER_TYPE, "2");
    Lexeme *z = newLexeme(ID_TYPE, "z");
    Lexeme *three = newLexeme(INTEGER_TYPE, "3");
    printf("Adding variable x with value 1\n");
    insertEnvironment(x, one, global);
    printf("Adding variable y with value 2\n");
    insertEnvironment(y, two, global);
    printf("Adding variable z with value 3\n");
    insertEnvironment(z, three, global);
    printEnvironment(stdout, global, false);

    // Extend environment
    printf("Extending the environment with w:4 and u:\"hello\"\n");
    Lexeme *w = newLexeme(ID_TYPE, "w");
    Lexeme *four = newLexeme(INTEGER_TYPE, "4");
    Lexeme *u = newLexeme(ID_TYPE, "u");
    Lexeme *hello = newLexeme(STRING_TYPE, "hello");
    Lexeme *local0 = extendEnvironment();

    return 0;
}
