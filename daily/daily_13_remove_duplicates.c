/*
 * File: remove_duplicates.c
 * Project: c
 * Created Date: Thu Feb 22 2024
 * Author: Frank
 * Last Modified: Thu Feb 22 2024
 * Modified By: Frank
 * Topic: [Remove Duplicates from Sorted Array](https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/727/)
 */


#include <stdio.h>

void print_array(int* nums, int n) {
    for (int i = 0; i < n; i++) printf("%d ", nums[i]);
    printf("\n");
}

void swap(int* nums, int k, int j) {
    if (k == j) return;
    nums[k] = nums[k] ^ nums[j];
    nums[j] = nums[k] ^ nums[j];
    nums[k] = nums[k] ^ nums[j];
}

int removeDuplicates(int* nums, int numsSize) {
    int n = numsSize;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] == nums[j]) {
                swap(nums, j, n - 1);
                n--;
                j--;
            } else if (nums[i] > nums[j]) {
                swap(nums, i, j);
            }
        }
    }
    return n;
}

int main() {
    int* nums;
    int n;

    nums = (int[]){ 0, 0, 4, 1, 1, 1, 2, 2, 3, 3, 4 };
    n = 11;
    print_array(nums, n);
    n = removeDuplicates(nums, n);
    print_array(nums, n);

    nums = (int[]){ 0, 0, 4, 1, 1, 1, 2, 2, 3, 5, 4, 5, 1 };
    n = 13;
    print_array(nums, n);
    n = removeDuplicates(nums, n);
    print_array(nums, n);
    return 0;
}