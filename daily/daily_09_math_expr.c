/*
 * File: daily_08_math_expr.c
 * Project: daily
 * Created Date: Thu Feb 15 2024
 * Author: Frank
 * Last Modified: Thu Feb 15 2024
 * Modified By: Frank
 * Topic: [](https://www.codewars.com/kata/52a78825cdfc2cfc87000005)
 */


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

struct Token {
    int token;
    double value;
};

char* tokstr[] = { "+", "-", "*", "/", "number", "(", ")", "EOF", "UNKNOWN" };

enum {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    NUMBER,
    LPAREN,
    RPAREN,
    T_EOF,
    T_UNKNOWN,
};

void print_token(struct Token* t) {
    printf("Token %s", tokstr[t->token]);
    if (t->token == NUMBER) printf(", value %f", t->value);
    printf("\n");
}

double scan_double(const char* expression, const char** endexpression) {
    char* endstr;
    double value = strtod(expression, &endstr);
    *endexpression = endstr;
    return value;
}

int scan(const char* expression, struct Token* t, const char** endexpression) {
    const char* pEnd = expression;
    // Skip as many whitespace characters as necessary.(?https://cplusplus.com/isspace)
    char c = *pEnd++;
    // printf("%c\n", c);
    while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) { c = *pEnd++; }

    switch (c) {
    case '\0':
        t->token = T_EOF;
        endexpression = NULL;
        return 0;
    case '+': t->token = PLUS; break;
    case '-':
        if (isdigit(*pEnd)) {
            pEnd--;
            t->token = NUMBER;
            t->value = scan_double(pEnd, &pEnd);
        } else {
            t->token = MINUS;
        }
        break;
    case '*': t->token = MULTIPLY; break;
    case '/': t->token = DIVIDE; break;
    case '(': t->token = LPAREN; break;
    case ')': t->token = RPAREN; break;
    // Scan literal number and convert it to double
    case '0' ... '9':
    case '.':
        pEnd--;
        t->token = NUMBER;
        t->value = scan_double(pEnd, &pEnd);
        break;
    default: t->token = T_UNKNOWN; break;
    }
    *endexpression = pEnd;
    return 1;
}

void lex(const char* expression) {
    printf("%s:\n", expression);
    struct Token t;
    const char* p = expression;
    while (scan(p, &t, &p)) {
        // printf("%s\n", p);
        print_token(&t);
    }
    printf("\n");
}

double calculate(const char* expression) {
    return 0;
}

int main() {
    // lex("2 + 32 * 5 - 8 / 31");
    // lex("2 + 32 * (5 - 8) / 31");
    lex("12*-1");
    lex("2 /2+3 * 4.75- -6");

    // calculate("1+1");
}