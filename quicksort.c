#include <stdio.h>

#define ARRAY_LENGTH(arr) (sizeof (arr) / sizeof ((arr)[0]))

void swap (int arr[], int i, int j) {
    if (i == j) return;
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    return;
}

void quicksort (int arr[], int left, int right) {
    if (left >= right) return;

    int pivot_pos = partition (arr, left, right);
    quicksort (arr, left, pivot_pos - 1);
    quicksort (arr, pivot_pos + 1, right);
}

int partition (int arr[], int left, int right) {
    // assume last element is the pivot
    int pivot = arr[right];
    int i = left;
    int j = right - 1;

    while (1) {
        while (i < right && arr[i] < pivot) i++;
        while (j >= left && arr[j] > pivot) j--;
        // printf("%d %d\n", i, j);

        if ((i - j) == 1) {
            break;
        }

        swap (arr, i, j);
    }
    printf ("%d %d\n", i, j);
    swap (arr, i, right);

    return i;
}

int main () {

    int numbers[] = { 25, 50, 10, 30, 80, 45, 25, 15, 80, 100, 60, 75 };
    printf ("%zu\n", ARRAY_LENGTH (numbers));

    quicksort (numbers, 0, ARRAY_LENGTH (numbers));

    for (size_t i = 0; i < ARRAY_LENGTH (numbers); i++) {
        printf ("%d ", numbers[i]);
    }
    printf ("\n");

    return 1;
}