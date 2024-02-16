/*
 * File: daily_08_math_expr.c
 * Project: daily
 * Created Date: Thu Feb 15 2024
 * Author: Frank
 * Last Modified: Thu Feb 15 2024
 * Modified By: Frank
 * Topic: [](https://www.codewars.com/kata/52a78825cdfc2cfc87000005)
 */


#include <stdio.h>
#include <stdlib.h>

struct Token {
    int token;
    double value;
};

enum {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    NUMBER,
};

char* tokstr[] = { "+", "-", "*", "/", "number" };

void print_token(struct Token* t) {
    printf("Token %s", tokstr[t->token]);
    if (t->token == NUMBER) printf(", value %f", t->value);
    printf("\n");
}

void lex(const char* expression) {
    char* pEnd = expression;
    int eof = 0;
    int i = 0;

    while (eof == 0) {
        char c = *pEnd++;
        // printf("%c\n", c);
        while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) { c = *pEnd++; }

        switch (c) {
        case '\0': eof = 1; break;
        case '+': t->token = PLUS; break;
        case '-': t->token = MINUS; break;
        case '*': t->token = MULTIPLY; break;
        case '/': t->token = DIVIDE; break;
        case '0' ... '9':
        case '.':
            pEnd--;
            t->value = strtod(pEnd, &pEnd);
            t->token = NUMBER;
            break;
        default:
            break;
        }
        // tokens[i++] = t;
        print_token(t);
    }

    // printf("Tokens %d:\n", i);
    // for(int j = 0; j < i; j++){
    //     print_token(tokens[i]);
    // }
}

double calculate(const char* expression) {
    return 0;
}

int main() {
    printf("%d\n", 1 - -1);
    lex("2 + 32 * 5 - 8 / 31");

    // calculate("1+1");
}