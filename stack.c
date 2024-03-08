#include <stdbool.h>
#include <stdio.h>

/*
Stack
push: '(', '{', '[''
pop: ')', '}',  ]'
*/
bool isValid(char* s) {
    char mapping[] = { [')'] = '(', ['}'] = '{', [']'] = '[' };
    char stack[5000];
    int p = -1;
    while (*s != '\0') {
        char c = *s;
        switch (c) {
        case '(':
        case '{':
        case '[':
            // push();
            p++;
            stack[p] = c;
            break;
        case ')':
        case '}':
        case ']':
            // pop();
            if (p >= 0 && stack[p] == mapping[c])
                p--;
            else
                return false;
            break;
        default: break;
        }
        s++;
    }
    return p == -1 ? true : false;
}

int main() {
    return 0;
}