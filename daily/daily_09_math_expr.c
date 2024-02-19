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

char* tokstr[] = { "+", "-", "*", "/", "u+", "u-", "number", "(", ")", "EOF", "UNKNOWN" };

enum {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    UNARY_PLUS,
    UNARY_MINUS,
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

double scan_double(const char** expression_ptr) {
    char* endstr;
    double value = strtod(*expression_ptr, &endstr);
    *expression_ptr = endstr;
    return value;
}

static struct Token pt = { T_UNKNOWN, 0 };

int scan(const char** expression_ptr, struct Token* t) {
    const char* pEnd = *expression_ptr;
    // Skip as many whitespace characters as necessary.(?https://cplusplus.com/isspace)
    char c = *pEnd;
    // printf("%c\n", c);
    while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
        pEnd++;
        c = *pEnd;
    }

    switch (c) {
    case '\0': t->token = T_EOF; return 0;
    case '+':
        printf("+ %d\n", pt.token);
        if (pt.token == NUMBER) {
            t->token = PLUS;
            pt.token = 
        } else {
            t->token = UNARY_PLUS;
        }
        break;
    case '-':
        // printf("- %d\n", pt.token);
        if (pt.token == NUMBER) {
            t->token = MINUS;
        } else {
            t->token = UNARY_MINUS;
        }
        // if (isdigit(*(pEnd + 1))) {
        //     t->token = NUMBER;
        //     t->value = scan_double(&pEnd);
        //     pEnd--;
        // } else {
        //     t->token = MINUS;
        // }
        break;
    case '*': t->token = MULTIPLY; break;
    case '/': t->token = DIVIDE; break;
    case '(': t->token = LPAREN; break;
    case ')': t->token = RPAREN; break;
    // Scan literal number and convert it to double
    case '0' ... '9':
    case '.':
        t->token = NUMBER;
        t->value = scan_double(&pEnd);
        pEnd--;
        break;
    default: t->token = T_UNKNOWN; break;
    }
    pEnd++;
    *expression_ptr = pEnd;
    pt.token == t->token;
    return 1;
}

void lex(const char* expression) {
    printf("%s:\n", expression);
    struct Token t;
    const char* p = expression;
    while (scan(&p, &t)) {
        // printf("%s\n", p);
        print_token(&t);
    }
    printf("\n");
}

/* BNF(Backus-Naur Form) grammar:
expression  :   term
            |   expression + expression
            |   expression - expression

term        :   factor
            |   term * term
            |   term / term

factor      :   NUMBER
            |   ( expression )
            |   -factor

*/
double parse_expression(const char** expression);
double parse_term(const char** expression_ptr);
double parse_factor(const char** expression_ptr);

double parse_factor(const char** expression_ptr) {
    struct Token t;
    printf("%s\n", *expression_ptr);
    scan(expression_ptr, &t);
    printf("%s\n", *expression_ptr);
    print_token(&t);
    if (t.token == NUMBER) return t.value;
    if (t.token == LPAREN) {
        double v = parse_expression(expression_ptr);
        expression_ptr++;
        return v;
    }
    if (t.token == UNARY_MINUS) { return -1 * parse_factor(expression_ptr); }
    if (t.token == UNARY_PLUS) { return parse_factor(expression_ptr); }
}

double parse_term(const char** expression) {
    const char* p = *expression;
    double left = parse_factor(&p);
    struct Token op;
    scan(&p, &op);
    // print_token(&op);
    while (1) {
        if (op.token == MULTIPLY) {
            left *= parse_factor(&p);
        } else if (op.token == DIVIDE) {
            left /= parse_factor(&p);
        } else {
            p--;
            break;
        }
        scan(&p, &op);
    }
    *expression = p;
    return left;
}

double parse_expression(const char** expression) {
    const char* p = *expression;
    double left = parse_term(&p);
    struct Token op;
    scan(&p, &op);
    print_token(&op);
    while (1) {
        if (op.token == T_EOF) {
            p--;
            break;
        } else if (op.token == RPAREN) {
            break;
        } else if (op.token == PLUS) {
            left += parse_term(&p);
        } else if (op.token == MINUS) {
            left -= parse_term(&p);
        }
        scan(&p, &op);
    }
    *expression = p;
    return left;
}

double calculate(const char* expression) {
    pt.token = T_UNKNOWN;
    return parse_expression(&expression);
}

int main() {
    // lex("-(4)");
    // lex("1-1");
    // lex("1 -1");
    // lex("1- -1");
    // lex("12*-1");
    // lex("2 + 32 * (5 - 8) / 31");
    // lex("12*- 1");
    lex("2 /2+3 * 4.75- -6");

    // calculate("1+1");
    // printf("%f\n", parse_expression(&(const char*){ "2+3*5" }));
    // printf("%f\n", parse_expression(&(const char*){ "12*-1" }));
    // printf("%f\n", parse_expression(&(const char*){ "1 - 1" }));
    // printf("%f\n", calculate("-123"));
    // printf("%f\n", parse_expression(&(const char*){ "2 /2+3 * 4.75- -6" }));
    // printf("%f\n", parse_expression(&(const char*){ "2 + 32 * 5 - 8 / 31" }));
    printf("21.25=%f\n", calculate("2 /2+3 * 4.75- -6"));
    // printf("-7=%f\n", calculate("((2+5)*(3-4))"));
    // printf("2=%f\n", calculate("6 + -(4)"));
}