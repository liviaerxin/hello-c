#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

struct interval {
    int first;
    int second;
};

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
    printf("pivot_pos: %d left: %d right:%d\n", pivot_pos, left, right);
    quicksort(arr, left, pivot_pos - 1);
    quicksort(arr, pivot_pos + 1, right);
}

int partition(int arr[], int left, int right) {
    // assume last element is the pivot
    printf("left: %d right:%d\n", left, right);

    int pivot = arr[right];
    int i = left;
    int j = right - 1;
    printf("%d %d\n", arr[i], pivot);

    while (1) {
        while (i < right && arr[i] < pivot) i++;
        while (j >= left && arr[j] > pivot) j--;
        printf("%d %d\n", i, j);

        if ((i - j) >= 0) {
            break;
        }

        swap(arr, i, j);
    }
    printf("%d %d\n", i, j);
    swap(arr, i, right);

    return i;
}

int sum_intervals(const struct interval* v, size_t n) {
    int* firsts = (int*)malloc(sizeof(int) * n);
    int* seconds = (int*)malloc(sizeof(int) * n);

    for (size_t i = 0; i < n; i++) {
        firsts[i] = v[i].first;
        seconds[i] = v[i].second;
    }

    quicksort(firsts, 0, n - 1);
    quicksort(seconds, 0, n - 1);

    for (size_t i = 0; i < n; i++) printf("%d ", firsts[i]);
    printf("\n");
    for (size_t i = 0; i < n; i++) printf("%d ", seconds[i]);
    printf("\n");

    int sum = 0;

    for (int i = 0; i < n - 1; i++) {
        if (seconds[i] < firsts[i + 1]) sum = firsts[i + 1] - seconds[i];
    }

    sum = seconds[n - 1] - firsts[0] - sum;

    printf("%d\n", sum);
    free(firsts);
    free(seconds);

    return sum;
}

typedef struct {
    int a[20];
    int size;
} Token;

Token* tokenize_word(const char* string) {
    Token* tk = (Token*)malloc(sizeof(Token));
    char buffer[20];
    int buffer_size = 0;

    int tokens_size = 0;
    int i = 0;

    while (1) {
        if (string[i] == ' ' || string[i] == '-' || string[i] == '\0') {
            char* t = buffer;
            if (buffer_size > 0) {
                buffer[buffer_size] = '\0';
                if (strcmp(t, "one") == 0) tk->a[tokens_size] = 1;
                if (strcmp(t, "two") == 0) tk->a[tokens_size] = 2;
                if (strcmp(t, "three") == 0) tk->a[tokens_size] = 3;
                if (strcmp(t, "four") == 0) tk->a[tokens_size] = 4;
                if (strcmp(t, "five") == 0) tk->a[tokens_size] = 5;
                if (strcmp(t, "six") == 0) tk->a[tokens_size] = 6;
                if (strcmp(t, "seven") == 0) tk->a[tokens_size] = 7;
                if (strcmp(t, "eight") == 0) tk->a[tokens_size] = 8;
                if (strcmp(t, "nine") == 0) tk->a[tokens_size] = 9;
                if (strcmp(t, "ten") == 0) tk->a[tokens_size] = 10;
                if (strcmp(t, "eleven") == 0) tk->a[tokens_size] = 11;
                if (strcmp(t, "twelve") == 0) tk->a[tokens_size] = 12;
                if (strcmp(t, "thirteen") == 0) tk->a[tokens_size] = 13;
                if (strcmp(t, "fourteen") == 0) tk->a[tokens_size] = 14;
                if (strcmp(t, "fifteen") == 0) tk->a[tokens_size] = 15;
                if (strcmp(t, "sixteen") == 0) tk->a[tokens_size] = 16;
                if (strcmp(t, "seventeen") == 0) tk->a[tokens_size] = 17;
                if (strcmp(t, "eighteen") == 0) tk->a[tokens_size] = 18;
                if (strcmp(t, "nineteen") == 0) tk->a[tokens_size] = 19;
                if (strcmp(t, "twenty") == 0) tk->a[tokens_size] = 20;
                if (strcmp(t, "thirty") == 0) tk->a[tokens_size] = 30;
                if (strcmp(t, "forty") == 0) tk->a[tokens_size] = 40;
                if (strcmp(t, "fifty") == 0) tk->a[tokens_size] = 50;
                if (strcmp(t, "sixty") == 0) tk->a[tokens_size] = 60;
                if (strcmp(t, "seventy") == 0) tk->a[tokens_size] = 70;
                if (strcmp(t, "eighty") == 0) tk->a[tokens_size] = 80;
                if (strcmp(t, "ninety") == 0) tk->a[tokens_size] = 90;
                if (strcmp(t, "hundred") == 0) tk->a[tokens_size] = 100;
                if (strcmp(t, "thousand") == 0) tk->a[tokens_size] = 1000;
                if (strcmp(t, "million") == 0) tk->a[tokens_size] = 1000 * 1000;
                if (strcmp(t, "and") == 0) {
                    buffer_size = 0;
                    buffer[buffer_size] = '\0';
                    continue;
                }

                printf("%s %d\n", t, buffer_size);

                tokens_size++;
                buffer_size = 0;
                buffer[buffer_size] = '\0';
            }
        }

        if (string[i] == '\0') break;

        if (string[i] >= 'a' && string[i] <= 'z') {
            buffer[buffer_size] = string[i];
            buffer_size++;
        }

        // printf("%c %d\n", string[i], buffer_size);
        i++;
    }

    tk->size = tokens_size;
    return tk;
}
// long parse_word(const char *string)
// {
//   printf("parse_word: %s\n", string);

//   int tk->a[tokens_size] = 0;
//   int i = 0;
//   char token[20];
//   int token_i = 0;

//   while (1)
//   {
//     if (string[i] == ' ' || string[i] == '-' || string[i] == '\0')
//     {
//       token_i = 0;
//       token[token_i] = '\0';
//     }

//     if (string[i] == '\0')
//       break;

//     token[token_i] = string[i];
//     printf("parse token: %s\n", token);

//     if (strcmp(t, "one") == 0)
//       tk->a[tokens_size] = 1;
//     if (strcmp(t, "two") == 0)
//       tk->a[tokens_size] = 2;
//     if (strcmp(t, "three") == 0)
//       tk->a[tokens_size] = 3;
//     if (strcmp(t, "four") == 0)
//       tk->a[tokens_size] = 4;
//     if (strcmp(t, "five") == 0)
//       tk->a[tokens_size] = 5;
//     if (strcmp(t, "six") == 0)
//       tk->a[tokens_size] = 6;
//     if (strcmp(t, "seven") == 0)
//       tk->a[tokens_size] = 7;
//     if (strcmp(t, "eight") == 0)
//       tk->a[tokens_size] = 8;
//     if (strcmp(t, "nine") == 0)
//       tk->a[tokens_size] = 9;
//     if (strcmp(t, "ten") == 0)
//       tk->a[tokens_size] = 10;
//     if (strcmp(t, "eleven") == 0)
//       tk->a[tokens_size] = 11;
//     if (strcmp(t, "twelve") == 0)
//       tk->a[tokens_size] = 12;
//     if (strcmp(t, "thirteen") == 0)
//       tk->a[tokens_size] = 13;
//     if (strcmp(t, "fourteen") == 0)
//       tk->a[tokens_size] = 14;
//     if (strcmp(t, "fifteen") == 0)
//       tk->a[tokens_size] = 15;
//     if (strcmp(t, "sixteen") == 0)
//       tk->a[tokens_size] = 16;
//     if (strcmp(t, "seventeen") == 0)
//       tk->a[tokens_size] = 17;
//     if (strcmp(t, "eighteen") == 0)
//       tk->a[tokens_size] = 18;
//     if (strcmp(t, "nineteen") == 0)
//       tk->a[tokens_size] = 19;
//     if (strcmp(t, "twenty") == 0)
//       tk->a[tokens_size] = 20;
//     if (strcmp(t, "thirty") == 0)
//       tk->a[tokens_size] = 30;
//     if (strcmp(t, "forty") == 0)
//       tk->a[tokens_size] = 40;
//     if (strcmp(t, "fifty") == 0)
//       tk->a[tokens_size] = 50;
//     if (strcmp(t, "sixty") == 0)
//       tk->a[tokens_size] = 60;
//     if (strcmp(t, "seventy") == 0)
//       tk->a[tokens_size] = 70;
//     if (strcmp(t, "eighty") == 0)
//       tk->a[tokens_size] = 80;
//     if (strcmp(t, "ninety") == 0)
//       tk->a[tokens_size] = 90;
//     if (strcmp(t, "hundred") == 0)
//       tk->a[tokens_size] = tk->a[tokens_size] * 100;
//     if (strcmp(t, "thousand") == 0)
//       tk->a[tokens_size] = tk->a[tokens_size] * 1000;

//     i++;
//     token_i++;
//   }

//   printf("%d\n", tk->a[tokens_size]);
// }

int main() {
    printf("interval!\n");
    sum_intervals((const struct interval[]){ { 1, 5 }, { 10, 20 }, { 1, 6 }, { 16, 19 }, { 5, 11 } }, 5);
    // sum_intervals((const struct interval[]){{1, 5}}, 1ul);
    // sum_intervals((const struct interval[]){{1, 5}, {6, 10}}, 2ul);
    // sum_intervals((const struct interval[]){{-5,-1}, {1, 5}}, 2ul);
    // sum_intervals((const struct interval[]){{-1000000000, 1000000000}}, 1ul);
    // printf("Interval 1: [%d, %d]\n", v[0].first, v[0].second);
    // printf("Interval 2: [%d, %d]\n", v[1].first, v[1].second);
    // quicksort((int[]){20, 10}, 0, 1);
    // 130
    // sum_intervals((const struct interval[]){{231, 255}, {127, 132}, {-73, -65},
    // {-231, -229}, {-228, -205}, {54, 55}, {198, 199}, {148, 171}, {-50, -47},
    // {213, 218}, {26, 31}, {62, 68}, {-175, -174}, {-146, -141}, {-5, 0}, {-117, -112}, {-100, -93}, {114, 115}}, 18);

    // "seven hundred eighty-three thousand nine hundred and nineteen"
    // nineteen, nine hundred, seven hundred eighty-three thousand

    char s[] = "ten";
    int hash = 0;
    int i = 0;
    while (s[i]) {
        hash = (hash << 8) + s[i];
        i++;
    }

    printf("%08x\n", hash);

    printf("%d \n", strcmp("ten", "ten"));
    printf("%d \n", strcmp("ten", "ten1"));
    printf("%d \n", strcmp("ten", "te"));

    // Token *t = tokenize_word("seven hundred eighty-three thousand nine hundred and nineteen");
    Token* t = tokenize_word("two million seven hundred eighty-three thousand "
                             "nine hundred and nineteen");

    printf("[");
    for (int i = t->size; i > 0; i--) {
        printf("%d ", t->a[i - 1]);
    }
    printf("]\n");

    int num = 0;
    int scale = 1;
    for (int i = t->size; i > 0; i--) {
        int n = t->a[i - 1];
        if (n == 100) {
            if (scale == 1000)
                scale = 100 * 1000;
            else if (scale == 1000 * 1000)
                scale = 100 * 1000 * 1000;
            else
                scale = 100;
        } else if (n == 1000) {
            if (scale == 1000 * 1000)
                scale = 1000 * 1000 * 1000;
            else
                scale = 1000;
        } else if (n == 1000 * 1000) {
            scale = 1000 * 1000;
        } else {
            num += n * scale;
        }
    }

    printf("num: %d\n", num);

    // char str[] = "seven hundred eighty-three thousand nine hundred and
    // nineteen"; char *pch = strtok(str, " ,.-"); while (pch != NULL)
    // {
    //   printf("%s\n", pch);
    //   pch = strtok(NULL, " -");
    // }
    return 0;
}