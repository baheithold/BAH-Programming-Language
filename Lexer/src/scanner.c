/*
 *  Author:         Brett Heithold
 *  File:           scanner.c
 *  Created:        10/22/2020
 *  Last Revised:   10/23/2020
 */


#include "../header/lexeme.h"
#include "../header/lexer.h"
#include "../header/types.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    // Check for 2 command-line arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: scanner <file>\n");
        return 1;
    }

    // Open file for reading and error check
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "Error: Failed to open file <%s>\n", argv[1]);
        return 1;
    }

    // Lexically analyze the provided file
    Lexeme *lexeme = lex(fp);
    while (getLexemeType(lexeme) != END_OF_INPUT) {
        //char *type = getLexemeType(lexeme);
        printLexeme(stdout, lexeme);
        fprintf(stdout, "\n");
        lexeme = lex(fp);
    }
    printLexeme(stdout, lexeme);
    fprintf(stdout, "\n");

    fclose(fp);
    return 0;
}
