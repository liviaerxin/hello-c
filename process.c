#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void fork_example() {
    pid_t pid = fork();
    if (pid > 0) {
        printf("Parent process with PID: %d\n", getpid());
    } else if (pid == 0) {
        printf("Child process with PID: %d\n", getpid());
    } else {
        perror("Fork failed\n");
        exit(1); // Exit with error code 1
    }
}


void fork_example_variable() {
    // Local variables in stack segment will be duplicated to child process with both value and memory address (virtual)
    int x = 5;
    pid_t pid = fork();
    if (pid > 0) {
        x = x + 5;
        printf("Parent process with PID: %d, x = %d, 0x%p\n", getpid(), x, &x);
    } else if (pid == 0) {
        x = x - 5; 
        printf("Child process with PID: %d, x = %d, 0x%p\n", getpid(), x, &x);
    } else {
        perror("Fork failed\n");
        exit(1); // Exit with error code 1
    }
}

int main() {
    // fork_example();
    fork_example_variable();
    return 0;
}