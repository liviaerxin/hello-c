/*
 * File: daily_12_3sum.c
 * Project: daily
 * Created Date: Fri Mar 08 2024
 * Author: Frank
 * Last Modified: Fri Mar 08 2024
 * Modified By: Frank
 * Topic: [3sum](https://leetcode.com/problems/3sum)
 */


#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

void swap(int arr[], int i, int j) {
    if (i == j) return;
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    return;
}

void quicksort(int arr[], int left, int right) {
    if (left >= right) return;

    int pivot_pos = partition(arr, left, right);
    quicksort(arr, left, pivot_pos - 1);
    quicksort(arr, pivot_pos + 1, right);
}

int partition(int arr[], int left, int right) {
    // assume last element is the pivot
    int pivot = arr[right];
    int i = left;
    int j = right - 1;

    while (1) {
        while (i < right && arr[i] < pivot) i++;
        while (j >= left && arr[j] >= pivot) j--;

        // printf("%d %d\n", i, j);
        if ((i - j) == 1) { break; }

        swap(arr, i, j);
    }
    // printf("%d %d\n", i, j);
    swap(arr, i, right);

    return i;
}
/**
 * https://leetcode.com/problems/3sum
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().

Pseudo: 
while i < n - 2;
    j = i + 1; k = n-1;
    for
        if nums[i] + nums[j] + nums[k] == 0;
            xxx
            do k--, until nums[k] < nums[k+1];
            do j++; until nums[j] > nums[j];
            record;
        if nums[i] + nums[j] + nums[k] > 0;
            do k--, until nums[k] < nums[k+1];
        if nums[i] + nums[j] + nums[k] < 0;
            do j++; until nums[j] > nums[j-1];
        if j = k; break
    do i++; until nums[i] > nums[i-1];
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    // Sort in non-decreasing order
    quicksort(nums, 0, numsSize - 1);

    int buffer_size = BUFFER_SIZE;
    int** triplet_arr = (int**)malloc(sizeof(int*) * buffer_size);
    int size = 0;

    if (nums[numsSize - 1] < 0) {
        *returnSize = size;
        *returnColumnSizes = NULL; //(int*)malloc(sizeof(int) * size);
        // for (int i = 0; i < size; i++) { (*returnColumnSizes)[i] = 3; }
    }

    int i, j, k;
    i = 0;
    while (i < numsSize - 2) {
        j = i + 1;
        k = numsSize - 1;
        while (j < k) {
            int sum3 = nums[i] + nums[j] + nums[k];
            if (sum3 == 0) {
                // Save triplet
                int* array = (int*)malloc(3 * sizeof(int));
                array[0] = nums[i];
                array[1] = nums[j];
                array[2] = nums[k];
                triplet_arr[size] = array;
                size++;
                // Extend triplet_arr size to double
                if (size == buffer_size) {
                    buffer_size = buffer_size + BUFFER_SIZE;
                    int* temp = (int**)realloc(triplet_arr, sizeof(int*) * buffer_size);
                    if (temp == NULL) {
                        printf("Memory reallocation failed.\n");
                        free(triplet_arr);
                        return NULL; // Exit with an error code
                    }
                    triplet_arr = temp;
                }

                do { k--; } while (nums[k] == nums[k + 1] && j < k);
                do { j++; } while (nums[j] == nums[j - 1] && j < k);
            } else if (sum3 > 0) {
                do { k--; } while (nums[k] == nums[k + 1] && j < k);
            } else if (sum3 < 0) {
                do { j++; } while (nums[j] == nums[j - 1] && j < k);
            }
        }

        do { i++; } while (nums[i] == nums[i - 1] && (i < numsSize - 2));
    }

    *returnSize = size;
    *returnColumnSizes = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) { (*returnColumnSizes)[i] = 3; }
    return triplet_arr;
}

int main(){
    
    return 0;
}