#include <stdio.h>
#include <string.h>

// `_Generic` introduced in C11 for generic selection
#define print_array(data, n) _Generic((*data), int: print_int, char: print_char)(data, n)

void print_int(const int* data, size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
}

void print_char(const char* data, size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf("%c ", data[i]);
    }
}

int main(void) {
    int int_array[3] = { 1, 2, 3 };
    const char* char_array = "hello world";

    print_array(int_array, 3);
    printf("\n");
    print_array(char_array, strlen(char_array));
    printf("\n");
}