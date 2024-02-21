#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULL_CHAR '\0'

void printBytes(const char* str) {
    while (*str != NULL_CHAR)
        // printf("%02X ", (unsigned char)*str++);
        // or,  %hh: unsigned char, %x: hex
        printf("0x%hhx ", *str++);
}

void printChars(const char* str) {
    while (*str != NULL_CHAR) printf("%c ", *str++);
}

char* strdup(const char* s) {
    size_t slen = strlen(s);
    char* result = malloc(slen + 1);
    if (result == NULL) { return NULL; }

    memcpy(result, s, slen + 1);
    return result;
}

int main() {
    char str[] = "Hello, World!";
    char* charPtr = str;

    // Print the memory address of the char* using %p
    printf("Memory address of the char*: %p\n", (void*)charPtr);

    // Print the string of the char* using %s
    printf("String in the char*: ");
    printf("%s", charPtr);
    printf("\n\n");

    // Print each byte in the char* using pointer arithmetic
    printf("Bytes  in the char*: ");
    printBytes(charPtr);
    printf("\n\n");

    // Print each char in the char* using pointer arithmetic
    printf("ASCII  in the char*: ");
    printChars(charPtr);
    printf("\n\n");

    // Define a string using raw bytes, `0x00`: NULL-terminated string
    char* bytePtr = "\x48\x65\x6c\x6c\x6f\x2c\x20\x57\x6f\x72\x6c\x64\x21\x00";
    // char* bytePtr = (char[]){0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x2C, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x21, 0x00};
    printf("String in the raw byte char*: ");
    printf("%s", bytePtr);
    printf("\n\n");

    char* utf8BytePtr = "\xe4\xbd\xa0\x00";
    printf("String in the utf8 byte char*: %s\n", utf8BytePtr);
    printf("Bytes  in the char*: ");
    printBytes(utf8BytePtr);
    printf("\n\n");

    char s1[20] = "String";
    char* s2 = strdup(s1);
    printf("%s\n", s2);

    return 0;
}
