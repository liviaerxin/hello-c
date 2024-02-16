/*
 * File: daily_08_count_change.c
 * Project: c
 * Created Date: Thu Feb 15 2024
 * Author: Frank
 * Last Modified: Thu Feb 15 2024
 * Modified By: Frank
 * Topic: [Counting Change Combinations](https://www.codewars.com/kata/541af676b589989aed0009e7)
 */
#include <stdio.h>

int count_change(int money, int n_coins, const int coins[n_coins]) {
    if (money == 0) return 1;
    if (money < 0) return 0;

    int count = 0;
    for (int i = n_coins; i > 0; i--) { count = count + count_change(money - coins[i - 1], i, coins); }
    return count;
}

int main() {
    printf("(4, [1,2])   : %d \n", count_change(4, 2, (int[]){ 1, 2 }));
    printf("(10, [5,2,3]): %d \n", count_change(10, 3, (int[]){ 5, 2, 3 }));
    printf("(11, [5,7])  : %d \n", count_change(11, 2, (int[]){ 5, 7 }));
}