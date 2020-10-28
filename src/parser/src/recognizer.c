/*
 *  Author:         Brett Heithold
 *  File:           recognizer.c
 *  Created on:     10/25/2020
 *  Last Revision:  10/27/2020
 */


#include "../../lexer/header/lexeme.h"
#include "../../lexer/header/types.h"
#include "../../lexer/header/lexer.h"
#include "../header/parser.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


/********** Helper Function Prototypes **********/

bool checkFileExtension(char *);


int main(int argc, char **argv) {

    // check number of command line arguments
    if (argc != 2) {
        fprintf(stdout, "Usage: recognizer <filename.bah>\n");
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

    initLexer(fp);
    advance();
    program();
    match(END_OF_INPUT);
    fprintf(stdout, "legal\n");

    fclose(fp);

    return 0;
}


bool checkFileExtension(char *filename) {
    assert(filename != NULL);
    int length = strlen(filename);
    if (length < 5) {
        fprintf(stdout, "ERROR: Invalid file name\n");
        return 1;
    }
    else if (filename[length - 4] != '.' || filename[length - 3] != 'b'
            || filename[length - 2] != 'a' || filename[length - 1] != 'h') {
        fprintf(stdout, "ERROR: Unrecognized file type\n");
        return false;
    }
    return true;
}
