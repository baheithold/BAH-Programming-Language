/*
 *  Author:         Brett Heithold
 *  File:           pp.c
 *  Created on:     11/10/2020
 *  Last revision:  11/10/2020
 */


#include "../header/prettyPrinter.h"
#include "../../lexer/header/lexeme.h"
#include "../../lexer/header/lexer.h"
#include "../../lexer/header/types.h"
#include "../../parser/header/parser.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


/********** Helper Function Prototypes **********/
bool checkFileExtension(char *);


int main(int argc, char **argv) {

    // check that the number of command line arguments is exactly 2
    if (argc != 2) {
        fprintf(stdout, "Usage: pp <filename.bah>\n");
        return 0;
    }

    // Open and error check file
    FILE *fp;
    if (checkFileExtension(argv[1])) {
        fp = fopen(argv[1], "r");
        if (!fp) {
            fprintf(stdout, "ERROR: Failed to open file <%s>\n", argv[1]);
            return 0;
        }
    }
    else {
        // Invalid file extension
        return 0;
    }

    initLexer(fp);
    advance();
    Lexeme *tree = program();
    prettyPrint(stdout, tree);
    match(END_OF_INPUT);

    fclose(fp);

    return 0;
}


bool checkFileExtension(char *filename) {
    assert(filename != NULL);
    int length = strlen(filename);
    int dotIndex = length - 4;
    int bIndex = length - 3;
    int aIndex = length - 2;
    int hIndex = length - 1;
    if (length < 5) {
        fprintf(stdout, "ERROR: Invalid file name\n");
        return 1;
    }
    else if (filename[dotIndex] != '.' || filename[bIndex] != 'b'
            || filename[aIndex] != 'a' || filename[hIndex] != 'h') {
        fprintf(stdout, "ERROR: Unrecognized file type\n");
        return false;
    }
    return true;
}
