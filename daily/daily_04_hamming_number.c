/*
 * File: daily_04_hamming_number.c
 * Project: daily
 * Created Date: Fri Feb 16 2024
 * Author: Frank
 * Last Modified: Fri Feb 16 2024
 * Modified By: Frank
 * Topic: 
 * - [Hamming Numbers](https://www.codewars.com/kata/526d84b98f428f14a60008da)
 * - [hamming numbers](https://en.wikipedia.org/wiki/Regular_number)
 * - [n-smooth numbers](https://en.wikipedia.org/wiki/Smooth_number)
 * Brief:
 * 36=2*2*3*3, factor: 2 and 3.
 */

#include <stdint.h>
#include <stdio.h>

int is_hamming_number (int n) {
    if (n == 1) return 1;
    if (n == 2) return 1;
    if (n == 3) return 1;
    if (n == 5) return 1;
    if (n % 2 == 0) return is_hamming_number (n / 2);
    if (n % 3 == 0) return is_hamming_number (n / 3);
    if (n % 5 == 0) return is_hamming_number (n / 5);
    return 0;
}

#define MIN(a, b) (a) > (b) ? (b) : (a)
#define MAX(a, b) (a) > (b) ? (a) : (b)

uint64_t hamber (int n) {
    uint64_t* h = (uint64_t*)malloc (sizeof (uint64_t) * n);

  h[0] = 1;
  uint64_t x2 = 2, x3 = 3, x5 = 5;

    int i2 = 0, i3 = 0, i5 = 0;
    for (int i = 1; i < n; i++) {
        h[i] = MIN (MIN (x2, x3), x5);
        if (h[i] == x2) x2 = h[++i2] * 2;
        if (h[i] == x3) x3 = h[++i3] * 3;
        if (h[i] == x5) x5 = h[++i5] * 5;
    }

    for (int i = 0; i < n; i++) printf ("%llu ", h[i]);
    printf ("\n");

    uint64_t hamber_n = h[n - 1];
    free (h);

    printf ("%llu\n", hamber_n);

  return hamber_n;
}

int main () {
    printf ("%d: %d\n", 32, is_hamming_number (32));
    printf ("%d: %d\n", 33, is_hamming_number (33));
    printf ("%d: %d\n", 34, is_hamming_number (34));
    printf ("%d: %d\n", 64, is_hamming_number (64));
    printf ("%d: %d\n", 400, is_hamming_number (400));
    printf ("%d: %d\n", 405, is_hamming_number (405));
    printf ("%d: %d\n", 4150000, is_hamming_number (4150000));

    printf ("%d: %d\n", 1000, hamber (1000));
}