#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* An array has int as its element, created with dynamical size
 */
void test_dynamic_array_of_ints() {
    int size = 5;
    int* ptr_arr = (int*)malloc(size * sizeof(int));

    // Allocate memory for each element
    for (int i = 0; i < size; i++) {
        ptr_arr[i] = i * 10;
    }

    // Access each element in the array
    for (int i = 0; i < size; ++i) {
        printf("Element %d: %p, Value: %d\n", i, &ptr_arr[i], ptr_arr[i]);
    }

    free(ptr_arr);
}

/* An array contain address/pointer as its element, created with static size
 */
void test_array_of_pointers_to_int() {
    // Initialize an array of pointers to int
    int* arr[3];
    int size = sizeof(arr) / sizeof(arr[0]);

    // Assign addresses directly
    /*
    int x = 10, y = 20, z = 30;
    ptr_arr[0] = &x;
    ptr_arr[1] = &y;
    ptr_arr[2] = &z;
    */

    // Allocate memory for each element
    for (int i = 0; i < 3; i++) {
        arr[i] = (int*)malloc(sizeof(int));
        *arr[i] = i * 10;
    }

    // Access each element and its pointing value in the array
    for (int i = 0; i < size; ++i) {
        printf("Element %d: %p, Value: %p, Pointing Value: %d\n", i, (void*)&arr[i], (void*)arr[i], *arr[i]);
    }

    // Don't forget to free dynamically allocated memory
    for (int i = 0; i < size; ++i) {
        free(arr[i]);
    }
}

/* An array contain address/pointer as its element, created with dynamical size
 */
void test_dynamic_array_of_pointers_to_int() {
    int size = 5;
    int** ptr_arr = malloc(size * sizeof(int*));

    // Allocate memory for each element
    for (int i = 0; i < size; i++) {
        ptr_arr[i] = (int*)malloc(sizeof(int));
        *ptr_arr[i] = i * 10;
    }

    // Access each element in the array
    for (int i = 0; i < size; ++i) {
        printf("Element %d: %p, Value: %p, Pointing Value: %d\n", i, &ptr_arr[i], ptr_arr[i], *ptr_arr[i]);
    }

    for (int i = 0; i < size; ++i) {
        free(ptr_arr[i]);
    }
}

int main() {
    /* Pointer arithmetic: + */
    int arr[] = { 1, 2, 3, 4, 5 };
    int* ptr = arr;

    printf("Initial address       : %p\n", ptr);
    // add 1 to the pointer, as it points to an integer, the returning pointer value will add 4.
    ptr = ptr + 1;
    printf("Address after adding 1: %p\n", ptr);

    // Using uintptr_t for pointer arithmetic
    uintptr_t ptr1 = (uintptr_t)&arr[2];
    uintptr_t ptr2 = (uintptr_t)&arr[4];
    uintptr_t diff = ptr2 - ptr1;
    printf("Difference between pointers: %zu bytes\n", (size_t)diff);

    /* Array of ints dynamically*/
    printf("\nArray of ints dynamically \n");
    test_dynamic_array_of_ints();

    /* Array of pointers to int*/
    printf("\nArray of pointers to int \n");
    test_array_of_pointers_to_int();

    /* Array of pointers to int dynamically. */
    printf("\nArray of pointers to int dynamically \n");
    test_dynamic_array_of_pointers_to_int();

    return 0;
}
