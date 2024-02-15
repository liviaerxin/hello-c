#include <stdio.h>

int main() {
    char nullCharacter = '\0';

    printf("Decimal: %d\n", nullCharacter);
    printf("Hexadecimal: 0x%02X\n", (unsigned char)nullCharacter);

    // Because string literals in C are null-terminated by default, the null character \0 is automatically added to the
    // end of the array. The `sizeof(str)` would be 14
    char str[] = "Hello, World!";
    printf("%s\n", str);

    printf("Size: %ld\n", sizeof(str));
    return 0;
}
