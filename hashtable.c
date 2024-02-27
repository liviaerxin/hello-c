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
} RandomizedSet;

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


RandomizedSet* randomizedSetCreate() {
    RandomizedSet* set = (RandomizedSet*)malloc(sizeof(RandomizedSet));
    set->size = 0;
    set->capacity = CAPACITY;
    for (int i = 0; i < CAPACITY; i++) set->items[i] = NULL;
    return set;
}

bool randomizedSetContain(RandomizedSet* obj, int val) {
    uint key = hashKey(val);
    Item* item = obj->items[key];
    while (item != NULL) {
        if (item->value == val) return true;
        item = item->next;
    }
    return false;
}

bool randomizedSetInsert(RandomizedSet* obj, int val) {
    if (randomizedSetContain(obj, val)) return false;

    uint key = hashKey(val);
    Item* new = itemCreate(val);
    new->next = obj->items[key];
    obj->items[key] = new;
    obj->size++;
    return true;
}

// bool randomizedSetRemove(RandomizedSet* obj, int val) {
//     uint key = hashKey(val);
//     Item* item = obj->items[key];
//     while (item != NULL) {
//         if (item->value == val) {
//             obj->size++;
//             obj->size--;
//             return true;}
//         item = item->next;
//     }
//     return false;
// }

// int randomizedSetGetRandom(RandomizedSet* obj) {
//     for (int i = 0; i < obj->capacity; i++) {
//         if (obj->items[i] != 0) return obj->items[i];
//     }

//     // Return the element at that index
//     return 0;
// }

void randomizedSetFree(RandomizedSet* obj) {
    for (int i = 0; i < obj->size; i++) free(obj->items[i]);
    free(obj);
}

void randomizedSetPrint(RandomizedSet* obj) {
    for (int i = 0; i < obj->capacity; i++) {
        Item* item = obj->items[i];
        if (item != NULL) {
            printf("idx: %d, value: %d, ", i, item->value);
            while (item->next != NULL) {
                printf(" value: %d,", item->next->value);
                item = item->next;
            }
            printf("\n\n");
        }
    }
}

int main() {
    srand(time(NULL)); // Seed for random number generation
    RandomizedSet* obj = randomizedSetCreate();
    randomizedSetInsert(obj, 1);
    randomizedSetInsert(obj, 2);
    randomizedSetInsert(obj, 3);
    randomizedSetInsert(obj, 4);

    randomizedSetInsert(obj, 11);

    randomizedSetPrint(obj);

    printf("randomizedSetContain(11): %d\n", randomizedSetContain(obj, 11));

    // randomizedSetRemove(obj, 3);
    // printf("randomizedSetGetRandom: %d\n", randomizedSetGetRandom(obj));

    // randomizedSetPrint(obj);

    randomizedSetFree(obj);
    return 0;
}