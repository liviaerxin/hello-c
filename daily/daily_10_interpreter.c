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

typedef int Type;

/* Status codes */
enum StatusCodes {
    OK_CODE = 0,    /* Success */
    EMPTY_CODE = 1, /* Input string consists entirely of whitespaces */
    /* 2, 3, ... */ /* Errors */
};

struct Token {
    int token;
    double value;
};

char* tokstr[] = { "+", "-", "*", "/", "%", "u+", "u-", "number", "(", ")", "=", "IDENT", "EOF", "UNKNOWN", "NULL" };

enum {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    REMAINDER,
    UNARY_PLUS,
    UNARY_MINUS,
    NUMBER,
    LPAREN,
    RPAREN,
    T_EQULAS,
    T_IDENT,
    T_EOF,
    T_UNKNOWN,
    T_NULL,
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

static char Text[10];

int scan_ident(const char** expression_ptr) {
    int i = 0;
    while (isalpha(**expression_ptr) || isdigit(**expression_ptr) || ('_' == **expression_ptr)) {
        Text[i++] = **expression_ptr;
        (*expression_ptr)++;
    }
    Text[i] = '\0';
    return i;
}

static struct Token PreviousToken = { T_NULL, 0 };
static struct Token PutbackToken = { T_NULL, 0 };


void putback(struct Token* t) {
    PutbackToken.token = t->token;
    PutbackToken.value = t->value;
}

void free_putback() {
    PutbackToken.token = T_NULL;
    PutbackToken.value = 0;
}

void free_previous() {
    PreviousToken.token = T_NULL;
    PreviousToken.value = 0;
}


int next(const char** expression_ptr, struct Token* t) {
    if (PutbackToken.token != T_NULL) {
        t->token = PutbackToken.token;
        t->value = PutbackToken.value;
        free_putback();
        return 1;
    }

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
        if (PreviousToken.token == NUMBER || PreviousToken.token == RPAREN) {
            t->token = PLUS;
        } else {
            t->token = UNARY_PLUS;
        }
        break;
    case '-':
        // printf("- %d\n", Previous.token);
        if (PreviousToken.token == NUMBER || PreviousToken.token == RPAREN) {
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
    case '%': t->token = REMAINDER; break;
    case '(': t->token = LPAREN; break;
    case ')': t->token = RPAREN; break;
    // Scan literal number and convert it to double
    case '0' ... '9':
    case '.':
        t->token = NUMBER;
        t->value = scan_double(&pEnd);
        pEnd--;
        break;
    case '=': t->token = T_EQULAS; break;
    case 'a' ... 'z':
    case 'A'... 'Z':
    case '_':
        scan_ident(expression_ptr);
        t->token = T_IDENT;
        break;
    default: t->token = T_UNKNOWN; break;
    }
    pEnd++;
    *expression_ptr = pEnd;
    PreviousToken.token = t->token;
    return 1;
}

void lex(const char* expression) {
    printf("%s:\n", expression);
    struct Token t;
    const char* p = expression;
    while (next(&p, &t)) {
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
            |   term % term

factor      :   NUMBER
            |   ( expression )
            |   -factor

*/
int parse_expression(const char** expression_ptr);
int parse_term(const char** expression_ptr);
int parse_factor(const char** expression_ptr);

int parse_factor(const char** expression_ptr) {
    struct Token t;
    // printf("%s\n", *expression_ptr);
    next(expression_ptr, &t);
    // printf("%s\n", *expression_ptr);
    // print_token(&t);
    if (t.token == NUMBER) return t.value;
    if (t.token == LPAREN) {
        int v = parse_expression(expression_ptr);
        expression_ptr++;
        return v;
    }
    if (t.token == UNARY_MINUS) { return -1 * parse_factor(expression_ptr); }
    if (t.token == UNARY_PLUS) { return parse_factor(expression_ptr); }
}

int parse_term(const char** expression_ptr) {
    int left = parse_factor(expression_ptr);
    struct Token op;
    next(expression_ptr, &op);
    // print_token(&op);
    while (1) {
        if (op.token == MULTIPLY) {
            left *= parse_factor(expression_ptr);
        } else if (op.token == DIVIDE) {
            left /= parse_factor(expression_ptr);
        } else if (op.token == REMAINDER) {
            left %= parse_factor(expression_ptr);
        } else {
            // p--;
            putback(&op);
            break;
        }
        next(expression_ptr, &op);
    }
    return left;
}

int parse_expression(const char** expression_ptr) {
    double left = parse_term(expression_ptr);
    struct Token op;
    next(expression_ptr, &op);
    // print_token(&op);
    while (1) {
        if (op.token == T_EOF) {
            // p--;
            putback(&op);
            break;
        } else if (op.token == RPAREN) {
            break;
        } else if (op.token == PLUS) {
            left += parse_term(expression_ptr);
        } else if (op.token == MINUS) {
            left -= parse_term(expression_ptr);
        }
        next(expression_ptr, &op);
    }
    return left;
}

int calculate(const char* expression) {
    free_previous();
    free_putback();
    return parse_expression(&expression);
}

/* initInterpreter: initialize the interpreter if necessary and return
   a status code (any value other than OK_CODE is treated as an error) */
int initInterpreter(void) {
    free_previous();
    free_putback();
    return OK_CODE;
}

/* closeInterpreter: close the interpreter and free memory if necessary */
void closeInterpreter(void) {
    free_previous();
    free_putback();
    return;
}

/* evaluate: evaluate the string expression, and return a status code
   (any value other than OK_CODE and EMPTY_CODE is treated as an error).
   The result of evaluating the expression is placed in a variable
   by the pointer 'result' if the function returns OK_CODE. */
int evaluate(char* input, int* result) {
    initInterpreter();
    *result = parse_expression(&input);
    return OK_CODE;
}

int main() {
    Type status;
    printf("%d\n", evaluate("1 + 1", &status));
    printf("%d\n", evaluate("8 / 4", &status));
    printf("%d\n", evaluate("7 % 4", &status));
}