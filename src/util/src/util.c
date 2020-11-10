/*
 *  Author:         Brett Heithold
 *  File:           util.c
 *  Created on:     11/9/2020
 *  Last revision:  11/9/2020
 */


#include "../header/util.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void assertBAHfileExtension(char *filename) {
    assert(filename != NULL);
    int length = strlen(filename);
    if (length < 5) {
        // invalid file name
        fatal("invalid file name\n");
    }
    else if (filename[length - 4] != '.' || filename[length - 3] != 'b'
            || filename[length - 2] != 'a' || filename[length - 1] != 'h') {
        fatal("unrecognized file type\n");
    }
}


void fatal(char *fmt, ...) {
    va_list ap;

    fprintf(stdout, "Fatal error -> ");
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    va_end(ap);

    exit(0);
}
