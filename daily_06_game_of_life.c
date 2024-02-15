#include <stdio.h>

int count_live_neighbors(int rows, int cols, int cells[rows][cols], int row, int col) {
    // printf("cell[%d,%d]: %d\n", row, col, cells[row][col]);
    int count = 0;
    for (int i = row - 1; i <= (row + 1); i++) {
        for (int j = col - 1; j <= (col + 1); j++) {
            if (i >= 0 && j >= 0 && i < rows && j < cols) {
                printf("cell[%d,%d]: %d\n", i, j, cells[i][j]);
                count += cells[i][j];
            }
        }
    }
    count--;
    return count;
}

int main() {
    printf("Hello, World!\n");

    int cells[10][10] = { { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
    int rows = 10;
    int cols = 10;
    // printf("rows %d, cols: %d\n", rows, cols);
    // printf("cell[%d,%d]: %d\n", 0, 0, cells[0][0]);

    printf("cell[%d,%d] Live: %d\n", 2, 3, count_live_neighbors(rows, cols, cells, 2, 3));
    printf("cell[%d,%d] Live: %d\n", 0, 0, count_live_neighbors(rows, cols, cells, 0, 0));

    return 0;
}