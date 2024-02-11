#include <stdio.h>
#include <stdint.h>

int is_hamming_number(int n) { 
    if (n == 1) return 1;
    if (n == 2) return 1;
    if (n == 3) return 1;
    if (n == 5) return 1;
    if (n % 2 == 0) return is_hamming_number(n/2);
    if (n % 3 == 0) return is_hamming_number(n/3);
    if (n % 5 == 0) return is_hamming_number(n/5);
    return 0;
}

uint64_t hamber(int nth)
{
    int i = 0, n = 1;
    while(i < nth){
        if(is_hamming_number(n)){
            i++;
        }
        n++;
    }
    n = n- 1;
    return n;
}

int main() {
    printf("%d: %d\n", 32, is_hamming_number(32));
    printf("%d: %d\n", 33, is_hamming_number(33));
    printf("%d: %d\n", 34, is_hamming_number(34));
    printf("%d: %d\n", 64, is_hamming_number(64));
    printf("%d: %d\n", 400, is_hamming_number(400));
    printf("%d: %d\n", 405, is_hamming_number(405));
    printf("%d: %d\n", 4150000, is_hamming_number(4150000));


    printf("%d: %d\n", 1000, hamber(1000));

}