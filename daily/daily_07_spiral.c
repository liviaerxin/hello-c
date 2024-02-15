#include <stdio.h>

void spiralize(unsigned n, int spiral[n][n]) {
    // mutate the spiral[][] 2D-array
}

void initialize(unsigned n, int spiral[n][n]) {
    // initialize the spiral[][] 2D-array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            spiral[i][j] = 1;
        }
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

    int array[][3] = {
        { 1, 2, 3 },
        { 4, 5, 6 },
    };

    printf("%d %d %d\n", array[0][0], array[0][1], array[0][2]);

    int n = 5;
    int spiral[n][n];

    initialize(n, spiral);
    print_array(n, spiral);
}