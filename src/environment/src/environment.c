/*
 *  Author:         Brett Heithold
 *  File:           environment.c
 *  created on:     10/31/2020
 *  Last Revision:  11/7/2020
 */


#include "../header/environment.h"
#include "../../lexer/header/lexeme.h"
#include "../../lexer/header/types.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>


#define DEBUG false


/********** Private Function Prototypes **********/
static bool    isSameVariable(Lexeme *, Lexeme *);


/********** Public Function Definitions **********/

Lexeme *createEnvironment(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: createEnvironment\n");
    }
    return extendEnvironment(NULL, NULL, NULL);
}

Lexeme *lookupEnvironment(Lexeme *variable, Lexeme *environment) {
    assert(variable != NULL);
    assert(environment != NULL);
    if (DEBUG) {
        fprintf(stdout, "CALL: lookupEnvironment\n");
    }

    while (environment != NULL) {
        Lexeme *vars = car(environment);
        Lexeme *vals = cadr(environment);
        while (vars != NULL) {
            if (isSameVariable(variable, car(vars))) {
                return car(vals);
            }
            vars = cdr(vars);
            vals = cdr(vals);
        }
        environment = cdr(cdr(environment));
    }
    fprintf(stdout, "ERROR: %s is undefined\n", getLexemeStringValue(variable));
    return NULL;
}

Lexeme *updateEnvironment(Lexeme *variable, Lexeme *value, Lexeme *environment) {
    assert(variable != NULL);
    assert(value != NULL);
    assert(environment != NULL);

    if (DEBUG) {
        fprintf(stdout, "CALL: updateEnvironment\n");
    }

    while (environment != NULL) {
        Lexeme *vars = car(environment);
        Lexeme *vals = cadr(environment);
        while (vars != NULL) {
            if (isSameVariable(variable, car(vars))) {
                return set_car(vals, value);
            }
            vars = cdr(vars);
            vals = cdr(vals);
        }
        environment = cdr(cdr(environment));
    }
    fprintf(stdout, "ERROR: %s is undefined\n", getLexemeStringValue(variable));
    return NULL;
}

Lexeme *insertEnvironment(Lexeme *variable, Lexeme *value, Lexeme *environment) {
    assert(variable != NULL);
    assert(value != NULL);
    assert(environment != NULL);

    if (DEBUG) {
        fprintf(stdout, "CALL: insertEnvironment\n");
    }

    set_car(environment, cons(JOIN, variable, car(environment)));
    set_car(cdr(environment), cons(JOIN, value, cadr(environment)));
    return value;
}

Lexeme *extendEnvironment(Lexeme *variables, Lexeme *values, Lexeme *environment) {
    if (DEBUG) {
        fprintf(stdout, "CALL: extendEnvironment\n");
    }

    return cons(ENVIRONMENT, variables, cons(ENVIRONMENT, values, environment));
}

void printEnvironment(FILE *fp, Lexeme *environment, bool local) {
    assert(environment != NULL);

    if (DEBUG) {
        fprintf(stdout, "CALL: printEnvironment\n");
    }

    int scopeLevel = 0;

    if (local) {
        fprintf(fp, "The local environment is:\n");
    }
    else {
        fprintf(fp, "The environment is:\n");
    }

    while (environment != NULL) {
        fprintf(fp, "Scope Level: %d\n", scopeLevel);
        Lexeme *vars = car(environment);
        Lexeme *vals = cadr(environment);
        while (vars != NULL) {
            fprintf(fp, "%s : ", getLexemeStringValue(car(vars)));
            printLexeme(fp, car(vals));
            fprintf(fp, "\n");
            vars = cdr(vars);
            vals = cdr(vals);
        }
        if (local) break;
        scopeLevel++;
        environment = cdr(cdr(environment));
    }
    fprintf(fp, "\n");
}


/********** Private Function Definitions **********/

bool isSameVariable(Lexeme *var1, Lexeme *var2) {
    assert(var1 != NULL);
    assert(var2 != NULL);

    if (DEBUG) {
        fprintf(stdout, "CALL: isSameVariable\n");
    }

    if (strcmp(getLexemeStringValue(var1), getLexemeStringValue(var2)) == 0) {
        return true;
    }
    return false;
}
