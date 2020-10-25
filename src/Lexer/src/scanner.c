/*
 *  Author:         Brett Heithold
 *  File:           scanner.c
 *  Created:        10/22/2020
 *  Last Revised:   10/24/2020
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
    char *type = getLexemeType(lexeme);
    while (type != END_OF_INPUT) {
        if (type != BAD_NUMBER && type != BAD_CHARACTER && type != BAD_STRING) {
            printLexeme(stdout, lexeme);
            fprintf(stdout, "\n");
        }
        else {
            printf("ERROR, line %d: ", getLexemeLineNumber(lexeme));
            printLexeme(stdout, lexeme);
            fprintf(stdout, "\n");
            return 0;
        }
        lexeme = lex(fp);
        type = getLexemeType(lexeme);
    }
    printLexeme(stdout, lexeme);
    fprintf(stdout, "\n");

    fclose(fp);
    return 0;
}
