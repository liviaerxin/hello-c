/*
 * File: daily_07_spiral.c
 * Project: daily
 * Created Date: Fri Feb 16 2024
 * Author: Frank
 * Last Modified: Fri Feb 16 2024
 * Modified By: Frank
 * Topic: [Make a spiral](https://www.codewars.com/kata/534e01fbbb17187c7e0000c6)
 */

#include <stdio.h>

void spiralize(unsigned n, int spiral[n][n]) {
    // mutate the spiral[][] 2D-array
    int top = 0, left = 0, bottom = n - 1, right = n - 1;
    while (top <= bottom && left <= right) {
        printf("top: %d, left: %d, bottom: %d, right: %d\n", top, left, bottom, right);
        for (int i = left; i <= right; i++) { spiral[top][i] = 1; }
        if (++top > bottom) break;
        spiral[top][right] = 1;
        if (++top > bottom) break;

        for (int i = top; i <= bottom; i++) { spiral[i][right] = 1; }
        if (--right < left) break;
        spiral[bottom][right] = 1;
        if (--right < left) break;

        for (int i = right; i >= left; i--) { spiral[bottom][i] = 1; }
        if (--bottom < top) break;
        spiral[bottom][left] = 1;
        if (--bottom < top) break;

        for (int i = bottom; i >= top; i--) { spiral[i][left] = 1; }
        if (++left > right) break;
        spiral[top][left] = 1;
        if (++left > right) break;
    }
}

void initialize(unsigned n, int spiral[n][n]) {
    // initialize the spiral[][] 2D-array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { spiral[i][j] = 0; }
    }
}

void print_array(unsigned n, int spiral[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%d ", spiral[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main() {

    int array[][4] = {
        { 1, 2, 3, 1 },
        { 4, 5, 6, 7 },
    };

    printf("%p %p %p %p\n", array, array[0], array[1], array[2]);
    printf("array[%d,%d]: %d\n", 0, 0, *((int*)array));
    printf("array[%d,%d]: %d\n", 1, 2, *((int*)array + 1 * 4 + 2));
    printf("array[%d,%d]: %d\n", 1, 3, *((int*)array + 1 * 4 + 3));

    int n = 5;
    int spiral[n][n];

    initialize(n, spiral);
    // Here done
    spiralize(n, spiral);
    print_array(n, spiral);
}