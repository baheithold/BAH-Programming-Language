/*
 *  Author:         Brett Heithold
 *  File:           environment.c
 *  created on:     10/31/2020
 *  Last Revision:  11/1/2020
 */


#include "../header/environment.h"
#include "../../lexer/header/lexeme.h"


#define DEBUG false


/********** Private Function Prototypes **********/
Lexeme *cons(char *, Lexeme *, Lexeme *);
Lexeme *car(Lexeme *);
Lexeme *cdr(Lexeme *);
Lexeme *cadr(Lexeme *);
void    set_car(Lexeme *, Lexeme *);
void    set_cdr(Lexeme *, Lexeme *);
bool    sameVariable(Lexeme *, Lexeme *);


/********** Public Function Definitions **********/

Lexeme *createEnvironment(void) {
    if (DEBUG) {
        fprintf(stdout, "CALL: createEnvironment\n");
    }
    return extend(NULL, NULL, NULL);
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
    fprintf(stdout, "%s is undefined\n", variable);
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
    fprintf(stdout, "%s is undefined\n", variable);
    return NULL;
}

Lexeme *insertEnvironment(Lexeme *variable, Lexeme *value, Lexeme *environment) {
    assert(variable != NULL);
    assert(value != NULL);
    assert(environment != NULL);

    if (DEBUG) {
        fprintf(stdout, "CALL: insertEnvironment\n");
    }

    set_car(environment, cons(JOIN, variable, car(env)));
    set_car(cdr(env), cons(JOIN, value, cadr(env)));
    return value;
}

Lexeme *extendEnvironment(Lexeme *variables, Lexeme *values, Lexeme *environment) {
    assert(variables != NULL);
    assert(values != NULL);
    assert(environment != NULL);

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
            fprintf("%s : ", getLexemeStringValue(car(vars)));
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

Lexeme *cons(char *type, Lexeme *left, Lexeme *right) {
    assert(type != NULL);

    if (DEBUG) {
        fprintf(stdout, "CALL: cons\n");
    }

    Lexeme *result = newLexeme(type, NULL);
    set_car(result, left);
    set_cdr(result, right);
    return result;
}

Lexeme *car(Lexeme *lexeme) {
    assert(lexeme != NULL);

    if (DEBUG) {
        fprintf(stdout, "CALL: car\n");
    }

    return getLexemeLeftChild(lexeme);
}

Lexeme *cdr(Lexeme *lexeme) {
    assert(lexeme != NULL);

    if (DEBUG) {
        fprintf(stdout, "CALL: cdr\n");
    }

    return getLexemeRightChild(lexeme);
}

Lexeme *cadr(Lexeme *lexeme) {
    assert(lexeme != NULL);

    if (DEBUG) {
        fprintf(stdout, "CALL: cadr\n");
    }

    return car(cdr(lexeme));
}

void set_car(Lexeme *parent, Lexeme *child) {
    assert(parent != NULL);

    if (DEBUG) {
        fprintf(stdout, "CALL: set_car\n");
    }

    setLexemeLeftChild(parent, child);
}

void set_cdr(Lexeme *parent, Lexeme *child) {
    assert(parent != NULL);

    if (DEBUG) {
        fprintf(stdout, "CALL: set_cdr\n");
    }

    setLexemeRightChild(parent, child);
}

bool isSameVariable(Lexeme *var1, Lexeme *var2) {
    assert(var1 != NULL)
    assert(var2 != NULL)

    if (DEBUG) {
        fprintf(stdout, "CALL: isSameVariable\n");
    }

}
