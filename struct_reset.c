#include <stdio.h>

struct X {
    char a[10];
    char b[20];
    int i;
    char* c;
    char* d[10];
};

static const struct X empty_x = { 0 };

print_X(struct X* p_x) {
    printf("a: %s\n", p_x->a);
    printf("b: %s\n", p_x->b);
    printf("i: %d\n", p_x->i);
    printf("c: %p\n", p_x->c);
    for (int i = 0; i < 10; i++) { printf("d[%d]: %p ", i, p_x->d[i]); }
    printf("\n");
};

int main() {
    // Declare an instance of struct X and initialize its members
    struct X x1 = {
        "stringA",                     // Initializing member 'a' with "stringA"
        "stringB",                     // Initializing member 'b' with "stringB"
        10,                            // Initializing member 'i' with value 10
        "stringC",                     // Initializing member 'c' with "stringC"
        { "arrayElem1", "arrayElem2" } // Initializing member 'd' with an array of strings
    };

    printf("Struct X:\n");
    print_X(&x1);

    // Reset x1
    x1 = empty_x;
    // memset(&x1, 0, sizeof(x1));      // Zero out the memory for a struct using `memset`

    printf("\nAfter reset Struct X:\n");
    print_X(&x1);

    return 0;
}