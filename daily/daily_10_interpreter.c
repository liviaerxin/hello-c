/*
 * File: daily_08_math_expr.c
 * Project: daily
 * Created Date: Thu Feb 15 2024
 * Author: Frank
 * Last Modified: Thu Feb 15 2024
 * Modified By: Frank
 * Topic: [Simpler Interactive Interpreter](https://www.codewars.com/kata/53005a7b26d12be55c000243)
 */

/* BNF(Backus-Naur Form) grammar:
expression  :   term
            |   expression `+` expression
            |   expression `-` expression

term        :   factor
            |   term `*` term
            |   term `/` term
            |   term `%` term

factor      :   NUMBER
            |   ID
            |   `(` expression `)`
            |   `u-`factor
            |   `u+`factor
            |   assignment

assignment  :   ID `=` expression

*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Status codes */
enum StatusCodes {
    OK_CODE = 0,    /* Success */
    EMPTY_CODE = 1, /* Input string consists entirely of whitespaces */
    ERROR_CODE = 2,
    /* 2, 3, ... */ /* Errors */
};


char* tokstr[] = { "+", "-", "*", "/", "%", "u+", "u-", "number", "(", ")", "=", "ID", "EOF", "UNKNOWN", "NULL" };

enum TokenType {
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
    EQULAS,
    ID,
    T_EOF,
    T_UNKNOWN,
    T_NULL,
};

struct Token {
    enum TokenType token;
    double value;
    char* identifier;
};

struct Symbol {
    char* identifier;
    double value;
};

static enum StatusCodes Code = OK_CODE;
static int Globs = 0;
static struct Symbol SymbolTable[100];
static struct Token PreviousToken = { T_NULL, 0, NULL };
static struct Token PutbackToken = { T_NULL, 0, NULL };


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

void free_code() {
    Code = OK_CODE;
}

void free_symboltable() {
    for (int i = 0; i < Globs; i++) {
        SymbolTable[i].identifier = NULL;
        SymbolTable[i].value = 0.0;
    }
}

char* strdup(char* s) {
    size_t slen = strlen(s);
    char* result = malloc(slen + 1);
    if (result == NULL) { return NULL; }

    memcpy(result, s, slen + 1);
    return result;
}

int find_symbol(const char* identifier, struct Symbol* s) {
    for (int i = 0; i < Globs; i++) {
        if (strcmp(SymbolTable[i].identifier, identifier) == 0) {
            printf("find_symbol %s, %f, %d\n", SymbolTable[i].identifier, SymbolTable[i].value, i);
            s->value = SymbolTable[i].value;
            s->identifier = strdup(SymbolTable[i].identifier);
            return 1;
        }
    }
    return 0;
}

int add_symbol(const char* identifier, double value) {
    printf("add_symbol %s, %f\n", identifier, value);
    // Variable found, update its value
    for (int i = 0; i < Globs; i++) {
        if (SymbolTable[i].identifier != NULL && strcmp(SymbolTable[i].identifier, identifier) == 0) {
            SymbolTable[i].value = value;
            return 1;
        }
    }

    //  Symbol table is full
    if (++Globs > 100) return 0;

    // Variable not found, add it to the symbol table
    SymbolTable[Globs - 1].identifier = strdup(identifier);
    SymbolTable[Globs - 1].value = value;
}

void print_token(struct Token* t) {
    printf("Token %s", tokstr[t->token]);
    if (t->token == NUMBER) printf(", value %f", t->value);
    if (t->token == ID) printf(", name %s", t->identifier);
    printf("\n");
}

double scan_double(const char** expression_ptr) {
    char* endstr;
    double value = strtod(*expression_ptr, &endstr);
    *expression_ptr = endstr;
    return value;
}

char* scan_id(const char** expression_ptr) {
    char buffer[20];
    int i = 0;
    while (isalpha(**expression_ptr) || isdigit(**expression_ptr) || ('_' == **expression_ptr)) {
        buffer[i++] = **expression_ptr;
        (*expression_ptr)++;
    }
    buffer[i] = '\0';
    return strdup(buffer);
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
        if (PreviousToken.token == NUMBER || PreviousToken.token == RPAREN || PreviousToken.token == ID) {
            t->token = PLUS;
        } else {
            t->token = UNARY_PLUS;
        }
        break;
    case '-':
        // printf("- %d\n", Previous.token);
        if (PreviousToken.token == NUMBER || PreviousToken.token == RPAREN || PreviousToken.token == ID) {
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
    // Scan identifier
    case '=': t->token = EQULAS; break;
    case 'a' ... 'z':
    case 'A' ... 'Z':
    case '_':
        t->identifier = scan_id(&pEnd);
        t->token = ID;
        pEnd--;
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

double parse_expression(const char** expression_ptr);
double parse_term(const char** expression_ptr);
double parse_factor(const char** expression_ptr);
double parse_assignment(const char** expression_ptr);

static int rparen = 0;

double parse_factor(const char** expression_ptr) {
    struct Token t;
    // printf("%s\n", *expression_ptr);
    next(expression_ptr, &t);
    // printf("%s\n", *expression_ptr);
    // print_token(&t);
    if (t.token == NUMBER)
        return t.value;
    else if (t.token == LPAREN) {
        rparen++;
        double v = parse_expression(expression_ptr);
        next(expression_ptr, &t);
        if (t.token == RPAREN) {
            rparen--;
            return v;
        }
        Code = ERROR_CODE;
    } else if (t.token == UNARY_MINUS) {
        double v = parse_factor(expression_ptr);
        if (Code == OK_CODE) return -1 * v;
        Code = ERROR_CODE;
    } else if (t.token == UNARY_PLUS) {
        double v = parse_factor(expression_ptr);
        if (Code == OK_CODE) return +1 * v;
        Code = ERROR_CODE;
    } else if (t.token == ID) {
        struct Token t1;
        next(expression_ptr, &t1);
        // print_token(&t1);
        if (t1.token == EQULAS) {
            double v = parse_expression(expression_ptr);
            if (Code == OK_CODE) {
                add_symbol(t.identifier, v);
                return v;
            } else {
                Code = ERROR_CODE;
            }
        } else {
            putback(&t1);
            struct Symbol s;
            if (find_symbol(t.identifier, &s))
                return s.value;
            else
                Code = ERROR_CODE;
        }
    } else if (t.token == T_EOF && Code != EMPTY_CODE) {
        Code = EMPTY_CODE;
    } else {
        Code = ERROR_CODE;
    }
    return 0.0;
}

double parse_term(const char** expression_ptr) {
    double left = parse_factor(expression_ptr);
    struct Token op;
    next(expression_ptr, &op);
    // print_token(&op);
    while (1) {
        if (op.token == MULTIPLY) {
            left *= parse_factor(expression_ptr);
        } else if (op.token == DIVIDE) {
            double right = parse_factor(expression_ptr);
            if ((int)right == 0) {
                Code = ERROR_CODE;
                return 0.0;
            } else {
                left /= right;
            }
        } else if (op.token == REMAINDER) {
            int right = parse_factor(expression_ptr);
            if (right == 0) {
                Code = ERROR_CODE;
                return 0.0;
            } else {
                left = (int)left % right;
            }
        } else {
            // p--;
            putback(&op);
            break;
        }
        next(expression_ptr, &op);
    }
    return left;
}

double parse_expression(const char** expression_ptr) {
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
            if (rparen > 0) {
                putback(&op);
                break;
            } else {
                Code = ERROR_CODE;
                return 0.0;
            }
        } else if (op.token == PLUS) {
            double v = parse_term(expression_ptr);
            if (Code != OK_CODE) {
                Code = ERROR_CODE;
                return 0.0;
            }
            left += v;
        } else if (op.token == MINUS) {
            double v = parse_term(expression_ptr);
            if (Code != OK_CODE) {
                Code = ERROR_CODE;
                return 0.0;
            }
            left -= v;
        } else {
            Code = ERROR_CODE;
            break;
        }
        next(expression_ptr, &op);
    }
    return left;
}

/* initInterpreter: initialize the interpreter if necessary and return
   a status code (any value other than OK_CODE is treated as an error) */
int initInterpreter(void) {
    return OK_CODE;
}

/* closeInterpreter: close the interpreter and free memory if necessary */
void closeInterpreter(void) {
    free_code();
    free_symboltable();
    free_previous();
    free_putback();
    rparen = 0;
    return;
}

/* evaluate: evaluate the string expression, and return a status code
   (any value other than OK_CODE and EMPTY_CODE is treated as an error).
   The result of evaluating the expression is placed in a variable
   by the pointer 'result' if the function returns OK_CODE. */
int evaluate(char* input, int* result) {
    printf("%s\n", input);
    free_code();
    free_previous();
    free_putback();
    rparen = 0;
    *result = parse_expression(&input);
    return Code;
}


int main() {
    lex("_count = 7");
    int result;
    printf("expr: 1 + 1, code: %d, result: %d\n\n", evaluate("1 + 1", &result), result);
    printf("expr: 8 / 4, code: %d, result: %d\n\n", evaluate("8 / 4", &result), result);
    printf("expr: 7 % 4, code: %d, result: %d\n\n", evaluate("7 % 4", &result), result);
    printf("expr: x = 7, code: %d, result: %d\n\n", evaluate("x = 7", &result), result);
    printf("expr: x, code: %d, result: %d\n\n", evaluate("x", &result), result);
    printf("expr: x + 1, code: %d, result: %d\n\n", evaluate("x + 1", &result), result);
    printf("expr: y, code: %d, result: %d\n\n", evaluate("y", &result), result);

    printf("expr: empty string, code: %d, result: %d\n\n", evaluate("  ", &result), result);
    printf("expr: 1 2, code: %d, result: %d\n\n", evaluate("1  2", &result), result);

    printf("expr: _count = 100, code: %d, result: %d\n\n", evaluate("_count = 100", &result), result);

    printf("expr: 100 / 0, code: %d, result: %d\n\n", evaluate("100 / 0", &result), result);
    printf("expr: / 100 +, code: %d, result: %d\n\n", evaluate("/ 100 +", &result), result);
    printf("expr: ((5, code: %d, result: %d\n\n", evaluate("((5", &result), result);

    printf("expr: +, code: %d, result: %d\n\n", evaluate("+", &result), result);

    printf("expr: 100 -, code: %d, result: %d\n\n", evaluate("100 -", &result), result);
    printf("expr: (, code: %d, result: %d\n\n", evaluate("(", &result), result);

    printf("expr: 200), code: %d, result: %d\n\n", evaluate("200)", &result), result);
    printf("expr: y=, code: %d, result: %d\n\n", evaluate("y=", &result), result);
}