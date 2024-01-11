/**
 * @file struct_align.c
 * @brief Memory align for `struct` follows the rules:
 * 1. The padding is inserted before each `field` to make the `field` start at an address that is divisible by its size. E.g. an `int` should start at an address divided by 4 and a `short` by 2.
 * 2. The padding is inserted after the whole `struct` to make the `field` in the next `struct` start at an address also divided by its size. So the size of the `struct` should be divided by the least common multiple(LCF) of each field size. E.g. if struct's largest field is `long` then the struct size is divide by 8.
 * In addition, the empty space between two `struct` could be used by non-struct variables that could sit in. 
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stddef.h>

// 4 + 1 -> (4) + (1) + 3 = 8
typedef struct
{
    int i;
    char c;
} StructA;

// 8 + 1 -> (8) + (1) + 7 = 16
typedef struct
{
    long l;
    char c;
} StructB;

// 1 + 8 -> (1) + 7 + (8) = 16
typedef struct
{
    char c;
    long l;
} StructB1;

// 4 + 8 + 1 -> (4) + 4 + (8) + (1) + 7 = 24
typedef struct
{
    int i;
    long l;
    char c;
} StructC;

// 8 + 4 + 1 -> (8) + (4) + (1) + 3 = 16
typedef struct
{
    long l;
    int i;
    char c;
} StructD;

// 4 + 1 + 8 + 1 -> (4) + (1) + 3 + (8) + (1) + 7 =24  
typedef struct {
    int i;
    char c;
    long l;
    char c1;
} StructE;

int main() {
    // StructA:
    printf("\n%s info,\n", "StructA");
    printf("Struct size: %zu bytes\n", sizeof(StructA));
    printf("Offset of i: %zu bytes\n", offsetof(StructA, i));
    printf("Offset of c: %zu bytes\n",  offsetof(StructA, c));

    // StructB:
    printf("\n%s info,\n", "StructB");
    printf("Struct size: %zu bytes\n", sizeof(StructB));
    printf("Offset of l: %zu bytes\n", offsetof(StructB, l));
    printf("Offset of c: %zu bytes\n",  offsetof(StructB, c));

    // StructB1:
    printf("\n%s info,\n", "StructB1");
    printf("Struct size: %zu bytes\n", sizeof(StructB1));
    printf("Offset of c: %zu bytes\n", offsetof(StructB1, c));
    printf("Offset of l: %zu bytes\n",  offsetof(StructB1, l));

    // StructC:
    printf("\n%s info,\n", "StructC");
    printf("Struct size: %zu bytes\n", sizeof(StructC));
    printf("Offset of i: %zu bytes\n", offsetof(StructC, i));
    printf("Offset of l: %zu bytes\n", offsetof(StructC, l));
    printf("Offset of c: %zu bytes\n",  offsetof(StructC, c));

    // StructD: saving 8 fewer bytes than `StructC` while having same fields in different order.
    printf("\n%s info,\n", "StructD");
    printf("Struct size: %zu bytes\n", sizeof(StructD));
    printf("Offset of l: %zu bytes\n", offsetof(StructD, l));
    printf("Offset of i: %zu bytes\n", offsetof(StructD, i));
    printf("Offset of c: %zu bytes\n",  offsetof(StructD, c));

    // StructE:
    printf("\n%s info,\n", "StructE");
    printf("Struct size: %zu bytes\n", sizeof(StructE));
    printf("Offset of i: %zu bytes\n", offsetof(StructE, i));
    printf("Offset of c: %zu bytes\n", offsetof(StructE, c));
    printf("Offset of l: %zu bytes\n",  offsetof(StructE, l));
    printf("Offset of c1: %zu bytes\n", offsetof(StructE, c1));

    return 0;
}
