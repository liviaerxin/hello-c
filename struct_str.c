#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t length;
    char data[1]; // flexible array member, NULL terminated in last element
} String;

/* Using String_SIZE instead of sizeof(String) saves 7 bytes per string in 64 bit machine
 */
#define String_SIZE (offsetof(String, data) + 1)

String* string_new_with_size(const char* str, size_t len) {
    String* s = malloc(String_SIZE + len);

    if (s == NULL) {
        // Handle allocation failure
        return NULL;
    }

    s->length = len;
    memcpy(s->data, str, len);
    s->data[len] = '\0';
    return s;
}

String* string_new(const char* str) {
    size_t len = strlen(str);
    return string_new_with_size(str, len);
}

void string_free(String* s) {
    free(s);
}

int main() {
    //
    printf("Struct String Size: %zu\n", sizeof(String));
    printf("Struct String Size: %zu\n", String_SIZE);

    String* s = string_new("Hello world!");

    if (s != NULL) {
        printf("Length: %zu\n", s->length);
        printf("Data: %s\n", s->data);
        printf("Size: %zu\n", sizeof(*s));
        string_free(s);
    }

    // Array of pointers to String struct, don't use an array of String struct as it allocate fixed memory
    printf("\nArray of pointers to String Struct \n");
    int array_size = 3;
    String* myArray[array_size];

    for (int i = 0; i < array_size; ++i) {
        int size_for_w = i + 10; // Vary the size of the flexible array
        myArray[i] = string_new_with_size("Hello world! Hello world! Hello world!", size_for_w);
    }

    // Access and print elements
    for (int i = 0; i < array_size; ++i) {
        printf("Element %d:\n", i);
        printf("Length: %zu\n", myArray[i]->length);
        printf("  Data: %s\n", myArray[i]->data);
    }

    // Free allocated memory
    for (int i = 0; i < array_size; ++i) {
        free(myArray[i]);
    }

    return 0;
}