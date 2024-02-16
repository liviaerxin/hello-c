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

struct token {
    int token;
    double n_value;
};

enum {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    NUMBER,
};

char* tokstr[] = { "+", "-", "*", "/", "number" };

void print_token(struct token* t) {
    printf("Token %s", tokstr[t->token]);
    // if (t->token == NUMBER) printf(", value %f", t->n_value);
    printf("\n");
}

double calculate(const char* expression) {
    while (*expression != '\0') {
        char c = *expression;
        while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
            expression++;
            c = *expression;
        }
        struct token t;
        switch (c) {
        case '\0': break;
        case '+': t.token = PLUS; break;
        case '-': t.token = MINUS; break;
        case '*': t.token = MULTIPLY; break;
        case '/': t.token = DIVIDE; break;
        default:
            t.token = NUMBER;
            break;
            ;
        }
        print_token(&t);
        expression++;
    }
}

float customAtoF(const char* str) {
    float result = 0.0;
    float decimalFactor = 0.1;
    int sign = 1;
    int i = 0;

    if (str[i] == '-') {
        sign = -1;
        i++;
    }

    while (str[i] != '\0') {
        if (str[i] == '.') {
            i++;
            while (str[i] != '\0') {
                result += (str[i] - '0') * decimalFactor;
                decimalFactor *= 0.1;
                i++;
            }
        } else {
            result = result * 10 + (str[i] - '0');
            i++;
        }
    }

    return sign * result;
}

int main() {
    char str[] = "42.195";
    float myFloat = customAtoF(str);
    printf("Converted float: %f\n", myFloat);

    printf("%d\n", 1 - -1);
    calculate("2 + 32 * 5 - 8 / 3");
}