// Here, I handle hash key collision by using separate chaining](https://en.wikipedia.org/wiki/Hash_table#Collision_resolution)
/*
* O(1) average time:
    - Insert
    - Delete
    - Search

* A very simple hash key function: hashkey = key % CAPACITY.
* Hash key collision resolution: Separate chaining.
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
} HashTable;

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


HashTable* hashTableCreate() {
    HashTable* set = (HashTable*)malloc(sizeof(HashTable));
    set->size = 0;
    set->capacity = CAPACITY;
    for (int i = 0; i < CAPACITY; i++) set->table[i] = NULL;
    return set;
}

bool hashTableContain(HashTable* obj, int key) {
    uint hashkey = hashKey(key);
    Bucket* item = obj->table[hashkey];
    while (item != NULL) {
        if (item->key == key) return true;
        item = item->next;
    }
    return false;
}

bool hashTableInsert(HashTable* obj, int key, int value) {
    if (hashTableContain(obj, key)) return false;

    uint hashkey = hashKey(key);
    // Put the new in the first.
    Bucket* new = itemCreate(key, value);
    new->next = obj->table[hashkey];
    obj->table[hashkey] = new;
    obj->size++;

    return true;
}

bool hashTableRemove(HashTable* obj, int key) {
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
            free(item);
            obj->size--;
            return true;
        }

        prev = item;
        item = item->next;
    }
    return false;
}

void hashTableFree(HashTable* obj) {
    for (int i = 0; i < obj->capacity; i++) {
        Bucket* item = obj->table[i];
        while (item != NULL) {
            free(item);
            item = item->next;
        }
    }
    free(obj);
}

void hashTablePrint(HashTable* obj) {
    printf("HashTable, size: %d, capacity: %d, elements:\n", obj->size, obj->capacity);
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
    printf("\n");
}

int main() {
    srand(time(NULL)); // Seed for random number generation
    HashTable* obj = hashTableCreate();
    hashTableInsert(obj, 1, 100);
    hashTableInsert(obj, 2, 200);
    hashTableInsert(obj, 3, 300);
    hashTableInsert(obj, 4, 400);

    hashTableInsert(obj, 11, 500);
    hashTableInsert(obj, 21, 5400);
    hashTableInsert(obj, 31, 100);

    hashTablePrint(obj);

    // printf("hashTableContain(11): %d\n", hashTableContain(obj, 11));

    hashTableRemove(obj, 3);
    hashTableRemove(obj, 31);
    hashTablePrint(obj);

    // printf("hashTableGetRandom: %d\n", hashTableGetRandom(obj));

    hashTableFree(obj);
    return 0;
}