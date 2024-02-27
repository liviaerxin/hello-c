/*
 * File: daily_11_regular_expression.c
 * Project: daily
 * Created Date: Wed Feb 21 2024
 * Author: Frank
 * Last Modified: Wed Feb 21 2024
 * Modified By: Frank
 * Topic: [Regular expression parser](https://www.codewars.com/kata/5470c635304c127cad000f0d)
 */


/* BNF
expression      :   term
                |   term `|` term

term            :   factor
                |   term term

factor          :   atom
                |   atom `*`

atom            :   CHAR
                | `(` expression `)`

CHAR            : any valid character except meta characters (e.g., "*", "|", "(")
*/

#include <stdio.h>

typedef struct RegExp RegExp;

RegExp* any();
RegExp* normal(char c);
RegExp* zeroOrMore(RegExp* starred);
RegExp* or (RegExp * left, RegExp* right);
RegExp* str(RegExp* first);
RegExp* add(RegExp* str, RegExp* next);

char* pretty(RegExp* r);

enum TokenType {
    CHAR,
    ANY,
    STAR,
    LPAREN,
    RPAREN,
    OR,
    T_EOF,
    T_NULL,
};

char* tokstr[] = { "char", ".", "*", "(", ")", "|", "EOF", "NULL" };

struct Token {
    enum TokenType type;
    char value;
};

static struct Token PutbackToken = { T_NULL, 0 };

void putback(struct Token* t) {
    PutbackToken.type = t->type;
    PutbackToken.value = t->value;
}

void free_putback() {
    PutbackToken.type = T_NULL;
    PutbackToken.value = 0;
}

struct Token next(char** expr_ptr) {
    struct Token t;

    if (PutbackToken.type != T_NULL) {
        t.type = PutbackToken.type;
        t.value = PutbackToken.value;
        free_putback();
        return t;
    }

    char c = **expr_ptr;

    switch (c) {
    case '\0': t.type = T_EOF; return t;
    case '(': t.type = LPAREN; break;
    case ')': t.type = RPAREN; break;
    case '.': t.type = ANY; break;
    case '*': t.type = STAR; break;
    case '|': t.type = OR; break;
    default:
        t.type = CHAR;
        t.value = c;
        break;
    }

    (*expr_ptr)++;
    return t;
}

void print_token(struct Token* t) {
    printf("Token %s", tokstr[t->type]);
    if (t->type == CHAR) printf(", value %c", t->value);
    printf("\n");
}

void lex(char* expression) {
    printf("%s:\n", expression);
    struct Token t;
    char* p = expression;
    t = next(&p);
    while (1) {
        print_token(&t);
        if (t.type == T_EOF) break;
        t = next(&p);
    }
    printf("\n");
}

static int ERROR = 0;

RegExp* parse_expression(char** ptr);
RegExp* parse_term(char** ptr);
RegExp* parse_factor(char** ptr);
RegExp* parse_atom(char** ptr);

RegExp* parse_atom(char** ptr) {
    RegExp* left = NULL;
    struct Token t;
    t = next(ptr);
    //   print_token(&t);
    if (t.type == CHAR) {
        left = normal(t.value);
    } else if (t.type == ANY) {
        left = any();
    } else if (t.type == LPAREN) {
        left = parse_expression(ptr);
        t = next(ptr);
        if (t.type != RPAREN) ERROR = 1;
    } else if (t.type == T_EOF || t.type == RPAREN) {
        putback(&t);
    } else {
        putback(&t);
        ERROR = 1;
    }

    return left;
}

RegExp* parse_factor(char** ptr) {
    RegExp* left = parse_atom(ptr);
    struct Token t;
    t = next(ptr);
    //   print_token(&t);
    if (t.type == STAR) {
        left = zeroOrMore(left);
    } else {
        putback(&t);
    }

    return left;
}

RegExp* parse_term(char** ptr) {
    RegExp* left = parse_factor(ptr);
    struct Token t;
    t = next(ptr);
    int first = 1;
    while (1) {
        //      print_token(&t);
        if (t.type == T_EOF || t.type == OR) {
            putback(&t);
            break;
        } else if (t.type == RPAREN) {
            putback(&t);
            break;
        } else {
            putback(&t);
            RegExp* right = parse_factor(ptr);
            if (first) {
                left = str(left);
                first = 0;
            }
            left = add(left, right);
        }
        t = next(ptr);
    }

    return left;
}

RegExp* parse_expression(char** ptr) {
    RegExp* left = parse_term(ptr);
    struct Token t;
    t = next(ptr);
    //   print_token(&t);
    if (t.type == OR) {
        RegExp* right = parse_term(ptr);
        left = or (left, right);
    } else if (t.type == T_EOF) {
        return left;
    } else {
        putback(&t);
    }

    return left;
}

RegExp* parseRegExp(char* input) {
    //   printf("\nexpr: %s\n", input);
    free_putback();
    ERROR = 0;
    RegExp* r = parse_expression(&input);
    if (ERROR)
        return NULL;
    else
        return r;
}

int main() {
    //   lex("(a.*)|(bb)");
    printf("expr: abcdef, pretty: %s\n", pretty(parseRegExp("abcdef")));
    //   printf("expr: (a.*)|(bb), pretty: %s\n", pretty(parseRegExp("(a.*)|(bb)")));
    return 0;
}