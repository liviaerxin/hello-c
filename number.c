#include <stdio.h>

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
    printf("%d\n", ~(-2)+1);
    int n = -2147483648;
    unsigned int m = n > 0 ? n : ~(n) + 1;
    printf("%d\n", ~(n)+1);
    return 0;
}