/*
 *  Author:         Brett Heithold
 *  File:           lexer.c
 *  Created:        10/21/2020
 *  Last Revised:   10/25/2020
 */


#include "../header/lexeme.h"
#include "../header/lexer.h"
#include "../header/types.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/********** Global Variables **********/

static FILE *fp;
static int currentLine = 1;


/********** Private Function Prototypes **********/

void skipWhiteSpace(FILE *);
void skipComment(FILE *);
bool commentPending(char);
bool numberPending(char);
char peek(FILE *);
Lexeme *lexNumber(FILE *);
Lexeme *lexString(FILE *);
Lexeme *lexKeywordOrID(FILE *);
bool isValidSymbol(char);
bool isValidCharacterForID(char);


/********** Public Function Definitions **********/

void initLexer(FILE *input) {
    fp = input;
}

Lexeme *lex(void) {
    skipWhiteSpace(fp);
    char ch = fgetc(fp);
    Lexeme *resultLexeme = newLexeme(NULL, NULL);
    setLexemeLineNumber(resultLexeme, currentLine);
    if (ch == EOF) {
        setLexemeType(resultLexeme, END_OF_INPUT);
        return resultLexeme;
    }
    switch (ch) {
        case '(': setLexemeType(resultLexeme, OPAREN); return resultLexeme;
        case ')': setLexemeType(resultLexeme, CPAREN); return resultLexeme;
        case '{': setLexemeType(resultLexeme, OBRACE); return resultLexeme;
        case '}': setLexemeType(resultLexeme, CBRACE); return resultLexeme;
        case ',': setLexemeType(resultLexeme, COMMA); return resultLexeme;
        case ';': setLexemeType(resultLexeme, SEMICOLON); return resultLexeme;
        case ':': setLexemeType(resultLexeme, COLON); return resultLexeme;
        case '.':
            if (isdigit(peek(fp))) {
                ungetc(ch, fp);
                return lexNumber(fp);
            }
            else { setLexemeType(resultLexeme, DOT_BINARY); return resultLexeme; }
        case '+':
            ch = fgetc(fp);
            switch (ch) {
                case '+': setLexemeType(resultLexeme, INCREMENT_UNARY); return resultLexeme;
                case '=': setLexemeType(resultLexeme, PLUS_ASSIGN_BINARY); return resultLexeme;
                default:
                    ungetc(ch, fp);
                    setLexemeType(resultLexeme, PLUS_BINARY);
                    return resultLexeme;
            }
        case '-':
            ch = fgetc(fp);
            switch (ch) {
                case '-': setLexemeType(resultLexeme, DECREMENT_UNARY); return resultLexeme;
                case '=': setLexemeType(resultLexeme, MINUS_ASSIGN_BINARY); return resultLexeme;
                default:
                    ungetc(ch, fp);
                    setLexemeType(resultLexeme, MINUS_BINARY);
                    return resultLexeme;
            }
        case '*':
            ch = fgetc(fp);
            switch (ch) {
                case '=': setLexemeType(resultLexeme, TIMES_ASSIGN_BINARY); return resultLexeme;
                default:
                    ungetc(ch, fp);
                    setLexemeType(resultLexeme, TIMES_BINARY);
                    return resultLexeme;
            }
        case '/':
            ch = fgetc(fp);
            switch (ch) {
                case '=': setLexemeType(resultLexeme, DIVIDE_ASSIGN_BINARY); return resultLexeme;
                default:
                    ungetc(ch, fp);
                    setLexemeType(resultLexeme, DIVIDE_BINARY);
                    return resultLexeme;
            }
        case '^':
            ch = fgetc(fp);
            switch (ch) {
                case '=': setLexemeType(resultLexeme, POW_ASSIGN_BINARY); return resultLexeme;
                default:
                    ungetc(ch, fp);
                    setLexemeType(resultLexeme, POW_BINARY);
                    return resultLexeme;
            }
        case '%':
            ch = fgetc(fp);
            switch (ch) {
                case '=': setLexemeType(resultLexeme, MODULO_ASSIGN_BINARY); return resultLexeme;
                default:
                    ungetc(ch, fp);
                    setLexemeType(resultLexeme, MODULO_BINARY);
                    return resultLexeme;
            }
        case '<':
            ch = fgetc(fp);
            switch (ch) {
                case '=': setLexemeType(resultLexeme, LESSER_EQUALS_COMPARATOR); return resultLexeme;
                default:
                    ungetc(ch, fp);
                    setLexemeType(resultLexeme, LESSER_THAN_COMPARATOR);
                    return resultLexeme;
            }
        case '>':
            ch = fgetc(fp);
            switch (ch) {
                case '=': setLexemeType(resultLexeme, GREATER_EQUALS_COMPARATOR); return resultLexeme;
                default:
                    ungetc(ch, fp);
                    setLexemeType(resultLexeme, GREATER_THAN_COMPARATOR);
                    return resultLexeme;
            }
        case '=':
            ch = fgetc(fp);
            switch (ch) {
                case '=': setLexemeType(resultLexeme, EQUALS_COMPARATOR); return resultLexeme;
                default:
                    ungetc(ch, fp);
                    setLexemeType(resultLexeme, ASSIGN_BINARY);
                    return resultLexeme;
            }
        case '!':
            ch = fgetc(fp);
            switch (ch) {
                case '=': setLexemeType(resultLexeme, NOT_EQUALS_COMPARATOR); return resultLexeme;
                default:
                    ungetc(ch, fp);
                    setLexemeType(resultLexeme, NEGATE_UNARY);
                    return resultLexeme;
            }
        default:
            if (isdigit(ch)) {
                ungetc(ch, fp);
                return lexNumber(fp);
            }
            else if (isalpha(ch) || isValidSymbol(ch)) {
                ungetc(ch, fp);
                return lexKeywordOrID(fp);
            }
            else if (ch == '\"') {
                return lexString(fp);
            }
            else {
                char *chStr = malloc(sizeof(char) * 2);
                chStr[0] = ch;
                chStr[1] = '\0';
                setLexemeType(resultLexeme, UNKNOWN);
                setLexemeValue(resultLexeme, chStr);
                return resultLexeme;
            }
    }
    char *chStr = malloc(sizeof(char) * 2);
    chStr[0] = ch;
    chStr[1] = '\0';
    setLexemeType(resultLexeme, BAD_CHARACTER);
    setLexemeValue(resultLexeme, chStr);
    setLexemeLineNumber(resultLexeme, currentLine);
    return resultLexeme;
}

int getLexerLineNumber(void) {
    return currentLine;
}


/********** Private Function Definitions **********/

void skipWhiteSpace(FILE *fp) {
    char ch = fgetc(fp);
    while (isspace(ch)) {
        if (ch == '\n') currentLine++;
        ch = fgetc(fp);
    }
    if (commentPending(ch)) {
        skipComment(fp);
        skipWhiteSpace(fp);
    }
    else ungetc(ch, fp);
}

void skipComment(FILE *fp) {
    char ch = fgetc(fp);
    while (ch != '\n') {
        ch = fgetc(fp);
    }
    currentLine++;
}

bool commentPending(char ch) {
    return ch == '#';
}

bool numberPending(char ch) {
    return isdigit(ch);
}

char peek(FILE *fp) {
    char ch = fgetc(fp);
    ungetc(ch, fp);
    return ch;
}

Lexeme *lexNumber(FILE *fp) {
    int length = 1;
    int index = 0;
    char *token = malloc(sizeof(char) * length);
    assert(token != NULL);
    bool isReal = false;

    Lexeme *resultLexeme = newLexeme(NULL, NULL);

    char ch = fgetc(fp);
    while (!feof(fp) && (isdigit(ch) || ch == '.')) {
        if (ch == '.') {
            // if a dot has not yet been encountered,
            // set isReal to true and continue, else return BAD_NUMBER Lexeme
            if (!isReal) isReal = true;
            else {
                char *chStr = malloc(sizeof(char) * 2);
                chStr[0] = ch;
                chStr[1] = '\0';
                setLexemeType(resultLexeme, BAD_NUMBER);
                setLexemeLineNumber(resultLexeme, currentLine);
                return resultLexeme;
            }
        }

        // add character to token
        token[index++] = ch;

        // grow token as needed
        if (index >= length) {
            length *= 2;
            token = realloc(token, length);
        }

        // get next character
        ch = fgetc(fp);
    }

    // pushback character that broke the loop
    ungetc(ch, fp);

    // add termination character to the end of token
    token[index] = '\0';

    // shrink token length to fit
    token = realloc(token, sizeof(char) * (index + 1));
    assert(token != NULL);

    // return appropriate Lexeme
    setLexemeType(resultLexeme, isReal ? REAL_TYPE : INTEGER_TYPE);
    setLexemeValue(resultLexeme, token);
    setLexemeLineNumber(resultLexeme, currentLine);
    return resultLexeme;
}

Lexeme *lexString(FILE *fp) {
    int length = 1;
    int index = 0;
    char *str = malloc(sizeof(char) * length);
    assert(str != NULL);

    Lexeme *resultLexeme = newLexeme(NULL, NULL);

    char ch = fgetc(fp);
    while (ch != '\"') {
        if (ch == EOF) {
            setLexemeType(resultLexeme, BAD_STRING);
            setLexemeLineNumber(resultLexeme, currentLine);
            return resultLexeme;
        }
        else if (ch == '\\') {
            // handle escape character
            ch = fgetc(fp);
        }
        else if (ch == '\n') currentLine++;
        str[index++] = ch;
        if (index >= length) {
            length *= 2;
            str = realloc(str, length);
        }
        ch = fgetc(fp);
    }

    // add termination character to the end of token
    str[index] = '\0';

    // shrink token length to fit
    str = realloc(str, sizeof(char) * (index + 1));
    assert(str != NULL);

    setLexemeType(resultLexeme, STRING_TYPE);
    setLexemeValue(resultLexeme, str);
    setLexemeLineNumber(resultLexeme, currentLine);
    return resultLexeme;
}

Lexeme *lexKeywordOrID(FILE *fp) {
    int length = 1;
    int index = 0;
    char *token = malloc(sizeof(char) * length);
    assert(token != NULL);

    char ch = fgetc(fp);
    while (!feof(fp) && isValidCharacterForID(ch)) {
        token[index++] = ch;
        if (index >= length) {
            length *= 2;
            token = realloc(token, length);
        }
        ch = fgetc(fp);
    }

    // pushback character that broke the loop
    ungetc(ch, fp);

    // add termination character to the end of token
    token[index] = '\0';

    // shrink token length to fit
    token = realloc(token, sizeof(char) * (index + 1));
    assert(token != NULL);

    // return appropriate Lexeme
    Lexeme *resultLexeme = newLexeme(NULL, NULL);
    setLexemeLineNumber(resultLexeme, currentLine);
    if (strcmp(token, "if") == 0) setLexemeType(resultLexeme, IF);
    else if (strcmp(token, "else") == 0) setLexemeType(resultLexeme, ELSE);
    else if (strcmp(token, "for") == 0) setLexemeType(resultLexeme, FOR);
    else if (strcmp(token, "while") == 0) setLexemeType(resultLexeme, WHILE);
    else if (strcmp(token, "function") == 0) setLexemeType(resultLexeme, FUNCTION);
    else if (strcmp(token, "var") == 0) setLexemeType(resultLexeme, VAR);
    else if (strcmp(token, "return") == 0) setLexemeType(resultLexeme, RETURN);
    else if (strcmp(token, "break") == 0) setLexemeType(resultLexeme, BREAK);
    else if (strcmp(token, "continue") == 0) setLexemeType(resultLexeme, CONTINUE);
    else if (strcmp(token, "class") == 0) setLexemeType(resultLexeme, CLASS);
    else if (strcmp(token, "lambda") == 0) setLexemeType(resultLexeme, LAMBDA);
    else if (strcmp(token, "void") == 0) setLexemeType(resultLexeme, VOID);
    else if (strcmp(token, "true") == 0) setLexemeType(resultLexeme, BOOLEAN_TYPE);
    else if (strcmp(token, "false") == 0) setLexemeType(resultLexeme, BOOLEAN_TYPE);
    else if (strcmp(token, "null") == 0) setLexemeType(resultLexeme, NULL_TYPE);
    else if (strcmp(token, "and") == 0) setLexemeType(resultLexeme, AND);
    else if (strcmp(token, "or") == 0) setLexemeType(resultLexeme, OR);
    else if (strcmp(token, "xor") == 0) setLexemeType(resultLexeme, XOR);
    else if (strcmp(token, "import") == 0) setLexemeType(resultLexeme, IMPORT);
    else if (strcmp(token, "print") == 0) setLexemeType(resultLexeme, PRINT);
    else if (strcmp(token, "println") == 0) setLexemeType(resultLexeme, PRINTLN);
    else {
        setLexemeType(resultLexeme, ID_TYPE);
        setLexemeValue(resultLexeme, token);
    }
    return resultLexeme;
}

bool isValidSymbol(char ch) {
    switch (ch) {
        case '_':
        case '?':
        case '@':
        case '&':
        case '~':
            return true;
        default:
            return false;
    }
}

bool isValidCharacterForID(char ch) {
    return isalpha(ch) || isdigit(ch) || isValidSymbol(ch);
}
