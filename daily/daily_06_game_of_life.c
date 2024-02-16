/*
 * File: daily_06_game_of_life.c
 * Project: daily
 * Created Date: Fri Feb 16 2024
 * Author: Frank
 * Last Modified: Fri Feb 16 2024
 * Modified By: Frank
 * Topic: [Conway's Game of Life - Unlimited Edition](https://www.codewars.com/kata/52423db9add6f6fc39000354)
 */


#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int rows;
    int cols;
    int **data;
} Grid;

int count_live_neighbors(int rows, int cols, int *cells[], int row,
                         int col)
{
    // printf("cell[%d,%d]: %d\n", row, col, cells[row][col]);
    int count = 0;
    for (int i = row - 1; i <= (row + 1); i++)
    {
        for (int j = col - 1; j <= (col + 1); j++)
        {
            if (i >= 0 && j >= 0 && i < rows && j < cols)
            {
                // printf("cell[%d,%d]: %d\n", i, j, cells[i][j]);
                count += cells[i][j];
            }
        }
    }
    count = count - cells[row][col];
    return count;
}

// Function to create a new grid with the specified dimensions
Grid *create_grid(int rows, int cols)
{
    Grid *grid = (Grid *)malloc(sizeof(Grid));
    grid->rows = rows;
    grid->cols = cols;

    // Allocate memory for the data array
    grid->data = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i)
    {
        grid->data[i] = (int *)malloc(cols * sizeof(int));
        // Initialize all cells to zero
        for (int j = 0; j < cols; ++j)
        {
            grid->data[i][j] = 0;
        }
    }

    return grid;
}

Grid *enlarge_grid(int rows, int cols, int *cells[], int generations)
{
    int large_rows = rows + 2 * generations;
    int large_cols = cols + 2 * generations;

    Grid *large_grid = create_grid(large_rows, large_cols);

    for (int i = 0; i < rows; ++i)
    {
        // Initialize all cells to zero
        for (int j = 0; j < cols; ++j)
        {
            large_grid->data[generations + i][generations + j] = cells[i][j];
        }
    }
    return large_grid;
}

void free_grid(Grid *grid)
{
    for (int i = 0; i < grid->rows; ++i)
    {
        free(grid->data[i]);
    }
    free(grid->data);
    free(grid);
}

void generate_next(Grid *grid)
{
    // assume stack is large enough
    int buffer[grid->rows][grid->cols];
    for (int i = 0; i < grid->rows; i++)
    {
        for (int j = 0; j < grid->cols; j++)
        {
            int live_neighbors = count_live_neighbors(grid->rows, grid->cols, grid->data, i, j);
            if (grid->data[i][j] == 1)
            {
                if (live_neighbors == 2 || live_neighbors == 3)
                {
                    buffer[i][j] = 1;
                }
                else
                {
                    buffer[i][j] = 0;
                }
            }
            else if (grid->data[i][j] == 0)
            {
                if (live_neighbors == 3)
                {
                    buffer[i][j] = 1;
                }
                else
                {
                    buffer[i][j] = 0;
                }
            }
        }
    }
    // Copy buffer
    for (int i = 0; i < grid->rows; i++)
    {
        for (int j = 0; j < grid->cols; j++)
        {
            grid->data[i][j] = buffer[i][j];
        }
    }
}

Grid *trim_grid(Grid *grid)
{
    int top = 0, left = 0;
    int bottom = grid->rows - 1, right = grid->cols - 1;

    while (top < grid->rows)
    {
        int i;
        for (i = 0; i < grid->cols; i++)
        {
            if (grid->data[top][i] > 0)
                break;
        }
        if (i == grid->cols)
            top++;
        else
            break;
    }

    while (bottom > 0)
    {
        int i;
        for (i = 0; i < grid->cols; i++)
        {
            if (grid->data[bottom][i] > 0)
                break;
        }
        if (i == grid->cols)
            bottom--;
        else
            break;
    }

    while (left < grid->cols)
    {
        int i;
        for (i = 0; i < grid->rows; i++)
        {
            if (grid->data[i][left] > 0)
                break;
        }
        if (i == grid->rows)
            left++;
        else
            break;
    }

    while (right > 0)
    {
        int i;
        for (i = 0; i < grid->rows; i++)
        {
            if (grid->data[i][right] > 0)
                break;
        }
        if (i == grid->rows)
            right--;
        else
            break;
    }
    // printf("trimmed: %d %d %d %d\n", top, left, bottom, right);

    int trim_rows = bottom - top + 1;
    int trim_cols = right - left + 1;

    // Allocate memory for the data array
    Grid *trim_grid = create_grid(trim_rows, trim_cols);
    for (int i = 0; i < trim_grid->rows; i++)
    {
        for (int j = 0; j < trim_grid->cols; j++)
        {
            trim_grid->data[i][j] = grid->data[i + top][j + left];
        }
    }

    return trim_grid;
}

void print_grid(Grid *grid)
{
    for (int i = 0; i < grid->rows; i++)
    {
        for (int j = 0; j < grid->cols; j++)
        {
            printf("%d ", grid->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    printf("Hello, World!\n");

    int *cells[] = {
        (int[]){1, 0, 0},
        (int[]){0, 1, 1},
        (int[]){1, 1, 0},
    };
    int rows = 3;
    int cols = 3;
    // printf("rows %d, cols: %d\n", rows, cols);
    // printf("cell[%d,%d]: %d\n", 0, 0, cells[0][0]);

    printf("cell[%d,%d] Live: %d\n", 1, 2,
           count_live_neighbors(rows, cols, cells, 1, 2));
    printf("cell[%d,%d] Live: %d\n", 0, 1,
           count_live_neighbors(rows, cols, cells, 0, 1));

    // Grid *grid = enlarge_grid(rows, cols, cells, 0);
    Grid *grid = enlarge_grid(rows, cols, cells, 1);
    print_grid(grid);

    // step 1
    generate_next(grid);
    print_grid(grid);

    // step 2
    // generate_next(grid);
    // print_grid(grid);

    Grid *t_grid = trim_grid(grid);
    print_grid(t_grid);

    free_grid(grid);
    free_grid(t_grid);

    return 0;
}