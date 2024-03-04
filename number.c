#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
    // printf("%d\n", -4);
    // printf("%d\n", -4 >> 1);
    // printf("%d\n", -1 >> 1);
    // printf("%d\n", -2 & 1);
    // printf("%d\n", -3 & 1);
    // printf("%d\n", 2 & 1);
    // printf("%d\n", 3 & 1);
    // printf("%d\n", 2 >> 1);
    // printf("%d\n", 1 >> 1);
    // printf("%d\n", 0 >> 1);
    printf("%d\n", -5 & 1);
    printf("%d\n", -5 >> 1);
    printf("%d\n", -3 & 1);
    printf("%d\n", -3 >> 1);
    printf("%d\n", ~(-2) + 1);

    // For signed int, convert -NUMBER to NUMBER
    int min_sint = -2147483648;
    unsigned int m = min_sint > 0 ? min_sint : ~(min_sint) + 1;
    printf("%d\n", ~(min_sint) + 1);

    // Random
    srand(time(NULL));
    printf("Random number between 0 and 9: %d\n", rand() % 10);
    printf("Random number between 0 and 1: %d\n", rand() % 2);

    // Reservoir sampling, randomly select `k` elements from unknown size `n`.
    int n = 20, k = 4;
    int n_data[n], reservoir[k];

    // Initialize the array with values 1 to 20
    for (int i = 0; i < n; i++) { n_data[i] = i + 1; }

    // Algorithm R
    for (int i = 0; i < k; i++) { reservoir[i] = n_data[i]; }
    for (int i = k; i < n; i++) {
        int j = rand() % (i + 1);
        if (j < k) reservoir[j] = n_data[i];
    }

    // Verify
    printf("Reservoir[%d]:", k);
    for (int i = 0; i < k; i++) printf(" %d", reservoir[i]);
    printf("\n");

    return 0;
}