/*
 * File: daily_01_fib_product.c
 * Project: daily
 * Created Date: Fri Feb 16 2024
 * Author: Frank
 * Last Modified: Fri Feb 16 2024
 * Modified By: Frank
 * Topic: [Product of consecutive Fib numbers](https://www.codewars.com/kata/5541f58a944b85ce6d00006a)
 */


#include <stdio.h>

float newton_sqrt(float x, float t) {
    float precision = 0.01;
    float t1 = x / 2 / t + t / 2;
    if ((t1 - t) < precision && (t - t1) < precision)
        return t1;
    else
        return newton_sqrt(x, t1);
}

float sqrt(float x) {
    float t0 = x / 4;
    return newton_sqrt(x, t0);
}

typedef unsigned long long ull;

ull fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib(n - 1) + fib(n - 2);
}

int main(void) {
    char c = 65;
    printf("%d  %c\n", c, c); // should print: 65 A

    int n = 65;
    printf("%d  %c\n", n, n); // should print: 65 A

    int nn = 66;
    if (nn >= 'a' && nn <= 'Z') {
        printf("%c\n", nn); // should print: 65 A
    }

    const unsigned expected[128] = { 0 };
    for (int i = 0; i < 128; i++) printf("%d ", expected[i]);
    printf("\n");

    printf("%f\n", newton_sqrt(4, 3));
    printf("%f\n", sqrt(4));
    printf("%f\n", newton_sqrt(5, 3));
    printf("%f\n", newton_sqrt(921, 30));
    printf("%f\n", sqrt(800));

    printf("fib %dth: %llu\n", 10, fib(10));
    printf("fib %dth: %llu\n", 20, fib(20));
    printf("fib %dth: %llu\n", 30, fib(30));

    int verify = 0;
    // ull prod = 800;
    // ull prod = 714;
    ull prod = 700;
    float small = sqrt(prod / 2);

    int i = 0;
    ull n0 = 0;
    ull n1 = 1;
    ull n2 = n0 + n1;
    while (n2 < small) // f(n-1) > sqrt(P)/2
    {
        n0 = n1;
        n1 = n2;
        n2 = n0 + n1;
        i++;
    }
    n0 = n1;
    n1 = n2;      // n1: f(n-1)
    n2 = n0 + n1; // n2: f(n)

    if (n1 * n2 == prod) // f(n-1) * f(n) == P
    {
        verify = 1;
        printf("%llu = %llu * %llu, %d\n", prod, n1, n2, verify);
    } else if (n1 * n2 < prod) // f(n-1) * f(n) < P while f(n)*f(n+1) > P
    {
        verify = 0;
        n0 = n1;
        n1 = n2;
        n2 = n0 + n1;
        printf("%llu < %llu * %llu, %d\n", prod, n1, n2, verify);
    } else // f(n-1) * f(n) > P
    {
        verify = 0;
        printf("%llu < %llu * %llu, %d\n", prod, n1, n2, verify);
    }
}