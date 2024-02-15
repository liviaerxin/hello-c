/*!
 * clang -Wall -Wextra -o dlopen_test.out dlopen_test.c -ldl
 * Usage:
 * ./dlopen_test.out ./libOpenCvSharpExtern.dylib
 * DYLD_PRINT_LIBRARIES=1 ./dlopen_test.out ./libOpenCvSharpExtern.dylib
 */

#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    void* handle;
    char* error;

    printf("dlopen sample");

    if (argc != 2) {
        fprintf(stderr, "Usage: %s {dylib_path}\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    dlclose(handle);

    return EXIT_SUCCESS;
}