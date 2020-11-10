/*
 *  Author:         Brett Heithold
 *  File:           filetester.c
 *  Created on:     11/9/2020
 *  Last revision:  11/9/2020
 */


#include "../header/util.h"

#include <stdio.h>


int main(int argc, char **argv) {

    // validate number of command line arguments
    if (argc != 2) {
        fatal("Usage: filetester <filename.extension>\n");
    }

    // Test file
    assertBAHfileExtension(argv[1]);

    fprintf(stdout, "legal\n");

    return 0;
}
