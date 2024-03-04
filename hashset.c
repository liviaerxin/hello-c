// Here, I handle hash key collision by using separate chaining](https://en.wikipedia.org/wiki/Hash_table#Collision_resolution)
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 10
#define uint unsigned int


typedef struct Item {
    int value;
    struct Item* next;
} Item;

typedef struct {
    Item* items[CAPACITY];
    int size;
    int capacity;
} hashSet;

uint hashKey(int value) {
    return value % CAPACITY;
}

Item* itemCreate(int value) {
    Item* new = (Item*)malloc(sizeof(Item));
    if (new == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    new->value = value;
    new->next = NULL;
    return new;
}


hashSet* hashSetCreate() {
    hashSet* set = (hashSet*)malloc(sizeof(hashSet));
    set->size = 0;
    set->capacity = CAPACITY;
    for (int i = 0; i < CAPACITY; i++) set->items[i] = NULL;
    return set;
}

bool hashSetContain(hashSet* obj, int val) {
    uint key = hashKey(val);
    Item* item = obj->items[key];
    while (item != NULL) {
        if (item->value == val) return true;
        item = item->next;
    }
    return false;
}

bool hashSetInsert(hashSet* obj, int val) {
    if (hashSetContain(obj, val)) return false;

    uint key = hashKey(val);
    // Put the new in the first.
    Item* new = itemCreate(val);
    new->next = obj->items[key];
    obj->items[key] = new;
    obj->size++;

    return true;
}

bool hashSetRemove(hashSet* obj, int val) {
    uint key = hashKey(val);
    Item* item = obj->items[key];
    Item* prev = NULL;
    while (item != NULL) {
        if (item->value == val) {
            if (prev == NULL) {
                // The first bucket to be removed
                obj->items[key] = item->next;
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

void hashSetFree(hashSet* obj) {
    for (int i = 0; i < obj->size; i++) free(obj->items[i]);
    free(obj);
}

void hashSetPrint(hashSet* obj) {
    printf("hash set, size: %d, capacity: %d, elements:\n", obj->size, obj->capacity);
    for (int i = 0; i < obj->capacity; i++) {
        Item* item = obj->items[i];
        if (item != NULL) {
            printf("hashkey: %d, value: %d, ", i, item->value);
            if (item->next != NULL) printf("chaining value:");
            while (item->next != NULL) {
                printf(" %d,", item->next->value);
                item = item->next;
            }
            printf("\n");
        }
    }
    // printf("\n");
}

int main() {
    srand(time(NULL)); // Seed for random number generation
    hashSet* obj = hashSetCreate();
    hashSetInsert(obj, 1);
    hashSetInsert(obj, 2);
    hashSetInsert(obj, 3);
    hashSetInsert(obj, 4);

    hashSetInsert(obj, 11);
    hashSetInsert(obj, 21);
    hashSetInsert(obj, 31);

    hashSetPrint(obj);

    // printf("hashSetContain(11): %d\n", hashSetContain(obj, 11));

    hashSetRemove(obj, 3);
    hashSetRemove(obj, 31);
    hashSetPrint(obj);

    // printf("hashSetGetRandom: %d\n", hashSetGetRandom(obj));

    hashSetFree(obj);
    return 0;
}