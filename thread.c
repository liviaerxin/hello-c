#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* print_message(void* arg) {
    char* msg = (char*)arg;
    printf("%s\n", msg);
}

int main() {
    pthread_t threads[2];
    const char* messages[2] = { "Thread 1: Hello, World!", "Thread 2: Goodbye, World!" };

    for (int i = 0; i < 2; i++) {
        printf("Main: creating thread %d\n", i);
        int rc = pthread_create(&threads[i], NULL, &print_message, (void*)messages[i]);
        if (rc) {
            printf("Error: unable to create thread, %d\n", rc);
            exit(1);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < 2; i++) { pthread_join(threads[i], NULL); }

    printf("Main: program completed. Exiting.\n");
    return 0;
}