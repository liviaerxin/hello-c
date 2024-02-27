#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 10
#define uint unsigned int

uint hashKey(int value) {
    return value % CAPACITY;
}

typedef struct {};

typedef struct {
    int items[CAPACITY];
    int size;
    int capacity;
} RandomizedSet;


RandomizedSet* randomizedSetCreate() {
    RandomizedSet* set = (RandomizedSet*)malloc(sizeof(RandomizedSet));
    set->size = 0;
    set->capacity = CAPACITY;
    for (int i = 0; i < CAPACITY; i++) set->items[i] = 0;
    return set;
}

bool randomizedSetInsert(RandomizedSet* obj, int val) {
    uint key = hashKey(val);
    if (obj->items[key] == val) return false;
    obj->items[key] = val;
    obj->size++;
    return true;
}

bool randomizedSetRemove(RandomizedSet* obj, int val) {
    uint key = hashKey(val);
    if (obj->items[key] == val) {
        obj->items[key] = 0;
        obj->size--;
        return true;
    }
    return false;
}

int randomizedSetGetRandom(RandomizedSet* obj) {
    for (int i = 0; i < obj->capacity; i++) {
        if (obj->items[i] != 0) return obj->items[i];
    }

    // Return the element at that index
    return 0;
}

void randomizedSetFree(RandomizedSet* obj) {
    free(obj);
}

void randomizedSetPrint(RandomizedSet* obj) {
    for (int i = 0; i < obj->capacity; i++) { printf("idx: %d, value: %d\n", i, obj->items[i]); }
    printf("\n\n");
}

int main() {
    srand(time(NULL)); // Seed for random number generation
    RandomizedSet* obj = randomizedSetCreate();
    randomizedSetInsert(obj, 1);
    randomizedSetInsert(obj, 2);
    randomizedSetInsert(obj, 3);
    randomizedSetInsert(obj, 4);

    printf("randomizedSetGetRandom: %d\n", randomizedSetGetRandom(obj));

    randomizedSetPrint(obj);

    randomizedSetRemove(obj, 3);
    printf("randomizedSetGetRandom: %d\n", randomizedSetGetRandom(obj));

    randomizedSetPrint(obj);

    randomizedSetFree(obj);
    return 0;
}