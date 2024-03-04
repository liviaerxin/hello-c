// Here, I handle hash key collision by using separate chaining](https://en.wikipedia.org/wiki/Hash_table#Collision_resolution)
/*
O(1) average time:
    - Insert
    - Delete
    - Search
    - getRandom

*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAPACITY 10
#define uint unsigned int


typedef struct Bucket {
    int key;
    int value;
    struct Bucket* next;
} Bucket;

typedef struct {
    Bucket* table[CAPACITY];
    int size;
    int capacity;
    Bucket* array[CAPACITY]; // an additional array to store address of inserted buckets to make getRandom() in O(1)
} RandomizedSet;

uint hashKey(int key) {
    return key % CAPACITY;
}

Bucket* itemCreate(int key, int value) {
    Bucket* new = (Bucket*)malloc(sizeof(Bucket));
    if (new == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    new->key = key;
    new->value = value;
    new->next = NULL;
    return new;
}


RandomizedSet* randomizedSetCreate() {
    RandomizedSet* set = (RandomizedSet*)malloc(sizeof(RandomizedSet));
    set->size = 0;
    set->capacity = CAPACITY;
    for (int i = 0; i < CAPACITY; i++) set->table[i] = NULL;
    for (int i = 0; i < CAPACITY; i++) set->array[i] = NULL;
    return set;
}

bool randomizedSetContain(RandomizedSet* obj, int key) {
    uint hashkey = hashKey(key);
    Bucket* item = obj->table[hashkey];
    while (item != NULL) {
        if (item->key == key) return true;
        item = item->next;
    }
    return false;
}

bool randomizedSetInsert(RandomizedSet* obj, int key) {
    if (randomizedSetContain(obj, key)) return false;

    uint hashkey = hashKey(key);
    // Put the new in the first.
    int value = obj->size;
    Bucket* new = itemCreate(key, value);
    new->next = obj->table[hashkey];

    obj->table[hashkey] = new;
    obj->array[obj->size] = new;
    obj->size++;

    return true;
}

bool randomizedSetRemove(RandomizedSet* obj, int key) {
    uint hashkey = hashKey(key);
    Bucket* item = obj->table[hashkey];
    Bucket* prev = NULL;
    while (item != NULL) {
        if (item->key == key) {
            if (prev == NULL) {
                // The first bucket to be removed
                obj->table[hashkey] = item->next;
            } else {
                // The non-first bucket to be removed
                prev->next = item->next;
            }

            // Replace with the last element in array
            int i = item->value;
            int last = obj->size - 1;
            obj->array[i] = obj->array[last];
            obj->array[i]->value = i;
            obj->array[last] = NULL;
            obj->size--;

            free(item);
            return true;
        }

        prev = item;
        item = item->next;
    }
    return false;
}

int randomizedSetGetRandom(RandomizedSet* obj) {
    int k = rand() % obj->size;
    Bucket* item = obj->array[k];
    return item->key;
}

void randomizedSetFree(RandomizedSet* obj) {
    // for (int i = 0; i < obj->capacity; i++) {
    //     Bucket* item = obj->table[i];
    //     while (item != NULL) {
    //         free(item);
    //         item = item->next;
    //     }
    // }
    for (int i = 0; i < obj->capacity; i++) {
        if (obj->array[i] != NULL) free(obj->array[i]);
    };
    free(obj);
}

void randomizedSetPrint(RandomizedSet* obj) {
    // Print table
    printf("RandomizedSet, size: %d, capacity: %d, elements:\n", obj->size, obj->capacity);
    for (int i = 0; i < obj->capacity; i++) {
        Bucket* item = obj->table[i];
        if (item != NULL) {
            printf("index: %d: [key: %d, value: %d] ", i, item->key, item->value);
            // if (item->next != NULL) printf("chaining value:");
            while (item->next != NULL) {
                printf("[key: %d, value: %d] ", item->next->key, item->next->value);
                item = item->next;
            }
            printf("\n");
        }
    }
    // Print array
    printf("array: [");
    for (int i = 0; i < obj->size; i++) { printf("%d ", obj->array[i]->key); }
    printf("]\n");

    printf("\n");
}

int main() {
    srand(time(NULL)); // Seed for random number generation
    RandomizedSet* obj = randomizedSetCreate();

    randomizedSetInsert(obj, 1);
    randomizedSetInsert(obj, 2);
    randomizedSetInsert(obj, 3);
    randomizedSetInsert(obj, 4);
    randomizedSetInsert(obj, 11);
    randomizedSetInsert(obj, 21);
    randomizedSetInsert(obj, 31);
    randomizedSetPrint(obj);

    // printf("hashTableContain(11): %d\n", hashTableContain(obj, 11));

    randomizedSetRemove(obj, 3);
    randomizedSetPrint(obj);

    randomizedSetRemove(obj, 31);
    randomizedSetPrint(obj);

    // printf("hashTableGetRandom: %d\n", hashTableGetRandom(obj));


    printf("randomizedSetGetRandom: %d\n", randomizedSetGetRandom(obj));

    // randomizedSetFree(obj);
    return 0;
}