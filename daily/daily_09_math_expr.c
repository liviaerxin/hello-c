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

double scan_double(const char* expression, const char** endptr) {
    char* endstr;
    double value = strtod(expression, &endstr);
    *endptr = endstr;
    return value;
}

int scan(const char* expression, struct Token* t, const char** endptr) {
    const char* pEnd = expression;
    // Skip as many whitespace characters as necessary.(?https://cplusplus.com/isspace)
    char c = *pEnd++;
    // printf("%c\n", c);
    while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) { c = *pEnd++; }

    switch (c) {
    case '\0':
        t->token = T_EOF;
        endptr = NULL;
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
    *endptr = pEnd;
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

double parse_factor(const char* expression, const char** endptr) {
    const char* p = expression;
    struct Token t;
    scan(p, &t, &p);
    *endptr = p;
    if (t.token == NUMBER) return t.value;
    if (t.token == LPAREN) return parse_expression(p, endptr);
}

double parse_term(const char* expression, const char** endptr) {
    const char* p = expression;
    double left = parse_factor(p, &p);
    struct Token op;
    scan(p, &op, &p);
    while (1) {
        if (op.token == MULTIPLY) {
            left *= parse_factor(p, &p);
        } else if (op.token == DIVIDE) {
            left /= parse_factor(p, &p);
        } else {
            break;
        }
        scan(p, &op, &p);
    }
    p--;
    *endptr = p;
    return left;
}

double parse_expression(const char** expression) {
    const char* p = *expression;
    double left = parse_term(p, &p);
    struct Token op;
    scan(p, &op, &p);
    // print_token(&op);
    while (1) {
        if (op.token == T_EOF) {
            break;
        } else if (op.token == PLUS) {
            left += parse_term(p, &p);
        } else if (op.token == MINUS) {
            left -= parse_term(p, &p);
        }
        scan(p, &op, &p);
    }
    p--;
    *expression = p; 
    return left;
}

double calculate(const char* expression) {
    return 0;
}

int main() {
    lex("2 + 3 * 5");
    // lex("2 + 32 * 5 - 8 / 31");
    // lex("2 + 32 * (5 - 8) / 31");
    // lex("12*-1");
    // lex("2 /2+3 * 4.75- -6");

    // calculate("1+1");
    printf("%f\n", parse_expression("2+3*5"));
    // printf("%f\n", parse_expression("2+3*5"));
    // printf("%f\n", parse_expression("12*-1"));
    // printf("%f\n", parse_expression("1 - 1"));
    // printf("%f\n", parse_expression("-123"));
    // printf("%f\n", parse_expression("2 /2+3 * 4.75- -6"));
    // printf("%f\n", parse_expression("2 + 32 * 5 - 8 / 31"));
}