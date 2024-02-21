/*
 * File: daily_11_regular_expression.c
 * Project: daily
 * Created Date: Wed Feb 21 2024
 * Author: Frank
 * Last Modified: Wed Feb 21 2024
 * Modified By: Frank
* Topic: [Regular expression parser](https://www.codewars.com/kata/5470c635304c127cad000f0d)
 */


#include <stdio.h>

/* BNF
<regex>     :   <term> 
            |   <regex> "|" <regex>

<term>      :   <factor> 
            |   <term> <term>

<factor>    :   <atom> 
            |   <factor> "*"
            
<atom>      :   <char> 
            | "(" <regex> ")"

<char>      : any valid character except metacharacters (e.g., "*", "|", "(")
*/

typedef struct RegExp RegExp;

RegExp* any ();
RegExp* normal (char c);
RegExp* zeroOrMore (RegExp *starred);
RegExp* or (RegExp *left, RegExp *right);
RegExp* str (RegExp *first);
RegExp* add (RegExp *str, RegExp *next);

char *pretty (RegExp *r);

enum TokenType {
  CHAR,
  ANY,
  STAR,
  LPAREN,
  RPAREN,
  OR,
  T_EOF,
};

char* tokstr[] = { "char", ".", "*", "(", ")", "|", "EOF"};

struct Token {
  enum TokenType type;
  char value;
};

struct Token next(const char** expr_ptr) {
  char c = **expr_ptr;

  struct Token t;
  switch (c) {
    case '\0':
      t.type = T_EOF;
      return t;
    case '(':
      t.type = LPAREN;
      break;
    case ')':
      t.type = RPAREN;
      break;
    case '.':
      t.type = ANY;
      break;
    case '*':
      t.type = STAR;
      break;
    case '|':
      t.type = OR;
      break;
    default:
      t.type = CHAR;
      t.value = c;
      break;
  }

  (*expr_ptr)++;
  return t;
}

void print_token(struct Token *t){
  printf("Token %s", tokstr[t->type]);
  if (t->type == CHAR) printf(", value %c", t->value);
  printf("\n");
}

void lex(const char* expression) {
    printf("%s:\n", expression);
    struct Token t;
    const char* p = expression;
    t = next(&p);
    while (1) {
      print_token(&t);
      if (t.type == T_EOF) break;
      t = next(&p);
    }
    printf("\n");
}

RegExp *parseRegExp (char *input) {
  RegExp *left;
  RegExp *right;
  int x = 0;
  struct Token t;
  const char* p = input;
  t = next(&p);
  while (1) {
    if (t.type == T_EOF) break;
    if (t.type == CHAR ) {
      if (x==0) {
        left = str(normal(t.value));
        x++;
      } else {
        right = normal(t.value);
        left = add(left, right);
      }
      
    } 
    t = next(&p);
  }
  return left;
}


int main() {
//   lex("(a.*)|(bb)");
  printf("expr: abcdef, pretty: %s\n", pretty(parseRegExp("abcdef")));
//   printf("expr: (a.*)|(bb), pretty: %s\n", pretty(parseRegExp("(a.*)|(bb)")));
  return 0;
}