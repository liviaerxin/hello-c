/*
 * File: daily_05_snail_sort.c
 * Project: daily
 * Created Date: Fri Feb 16 2024
 * Author: Frank
 * Last Modified: Fri Feb 16 2024
 * Modified By: Frank
 * Topic: [Snail](https://www.codewars.com/kata/521c2db8ddc89b9b7a0000c1)
 */


#include <stdio.h>

void snail(int row, int colum, int matrix[row][colum], int* result) {
    int top = 0, bottom = row - 1, left = 0, right = colum - 1;
    int count = 0;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) result[count++] = matrix[top][i];
        for (int i = top + 1; i <= bottom; i++) result[count++] = matrix[i][right];
        for (int i = right - 1; i >= left; i--) result[count++] = matrix[bottom][i];
        for (int i = bottom - 1; i >= top + 1; i--) result[count++] = matrix[i][left];
        top++;
        left++;
        bottom--;
        right--;
    }
}

int main() {
    int matrix[4][4] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 },
        { 13, 14, 15, 16 },
    };
    int row = 4, colum = 4;
    int result[row * colum];
    snail(row, colum, matrix, result);

    for (int i = 0; i < row * colum; i++) printf("%d ", result[i]);
    printf("\n");
}