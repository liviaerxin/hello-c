#include <stdio.h>

void swap(int arr[], int i, int j) {
    arr[i] = arr[i] ^ arr[j];
    arr[j] = arr[i] ^ arr[j];
    arr[i] = arr[i] ^ arr[j];
}

int main() {
    int arr[] = { 1, 2, 0, 1, 0, 1, 0, 3, 0, 1 };
    int size = sizeof(arr) / sizeof(arr[0]);

    // swap(arr, 0, 1);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int i = 0, j = 0;
    for (i = 0; i < size; i++) {
        if (arr[i] == 0) {
            for (j = i + 1; j < size; j++) {
                if (arr[j] != 0) {
                    swap(arr, i, j);
                    break;
                }
            }

            if (j == size) {
                break;
            }
        }
    }

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}