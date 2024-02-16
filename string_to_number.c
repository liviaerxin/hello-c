#include <stdio.h>  // printf
#include <stdlib.h> // atof, strtod

float customAtoF(const char* str) {
    float result = 0.0;
    float decimalFactor = 0.1;
    int sign = 1;
    int i = 0;

    if (str[i] == '-') {
        sign = -1;
        i++;
    }

    while (str[i] != '\0') {
        if (str[i] == '.') {
            i++;
            while (str[i] != '\0') {
                result += (str[i] - '0') * decimalFactor;
                decimalFactor *= 0.1;
                i++;
            }
        } else {
            result = result * 10 + (str[i] - '0');
            i++;
        }
    }

    return sign * result;
}

int main() {
    // Use `atof(const char* str)`
    printf("\nUse `atof()`:\n");
    printf("string to double: %f\n", atof("1234567890.1234567"));
    printf("string to double: %f\n", atof("  1234567890.1234567"));
    printf("string to double: %f\n", atof("aaa1234567890.1234567  "));
    printf("string to double: %f\n", atof("1234567890.1234567  222"));
    printf("string to double: %f\n", atof("1234567890"));
    printf("string to double: %f\n", atof("1234567890,22"));
    printf("string to double: %f\n", atof("1234567890aa"));

    // Use `strtod()`
    printf("\nUse `strtod()`:\n");
    printf("string to double: %f\n", strtod("1234567890.1234567", NULL));
    printf("string to double: %f\n", strtod("aaa1234567890.1234567", NULL));

    char szOrbits[] = "  365.24   29.53";
    char* pEnd;
    double d1 = strtod(szOrbits, &pEnd);
    printf("string to double: %f, next string: %s\n", d1, pEnd);
    double d2 = strtod(pEnd, &pEnd);
    printf("string to double: %f, next string: %s\n", d2, pEnd);

    // Use `customAtoF()`
    printf("\nUse `customAtoF()`:\n");
    printf("string to float: %f\n", customAtoF("42.195"));
    // printf("string to double: %f\n", customAtoF("  1234567890.1234567"));
    // printf("string to double: %f\n", customAtoF("1234567890.1234567  "));
    // printf("string to double: %f\n", customAtoF("1234567890.1234567  222"));
    // printf("string to double: %f\n", customAtoF("1234567890"));


    return 0;
}