/*
 * File: hashtable_generic.c
 * Project: c
 * Created Date: Mon Mar 11 2024
 * Author: Frank
 * Last Modified: Mon Mar 11 2024
 * Modified By: Frank
 *
 * Implement a generic hash table for storing key-value pairs:
    - hashTableCreate(int capacity) Initialize the hash table with positive size capacity.
    - void* get(int key) Return the the value if the key exists, otherwise return NULL.
    - bool insert(int key, int value) Insert the key-value pair if the key not exist, and return true. Otherwise return false.
    - bool remove(int key) Remove the key if key exists and return true, otherwise return false.
 * The functions: get(), insert(), remove() must each run in O(1) average time complexity.
 *
 * Example:
    HashTable ht = hashTableCreate(2);
    ht.insert(1, 1);    // hashtable is {1=1}
    ht.insert(2, 2);    // hashtable is {1=1, 2=2}
    ht.get(3);          // returns -1 (not found)
    ht.insert(3, 3);    // hashtable is {1=1, 2=2, 3=3}
    ht.get(1);          // return 1
    ht.insert(4, 4);    // hashtable is {1=1, 2=2, 3=3, 4=4}
    ht.get(5);          // return -1 (not found)
    ht.get(3);          // return 3
    ht.get(4);          // return 4
 */
// https://www.w3resource.com/c-programming-exercises/hash/c-hash-exercises-9.php
// https://www.andreinc.net/2021/10/02/implementing-hash-tables-in-c-part-1
// https://github.com/nomemory/chained-hash-table-c
// https://www.andreinc.net/2021/10/02/implementing-hash-tables-in-c-part-1

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#pragma region HashTable

typedef unsigned long (*HashFunction)(const void* key);

// Linked list to implement separate chaining to handle key collision
typedef struct Bucket {
    int key;
    void* value;
    struct Bucket* next;
} Bucket;

typedef struct {
    Bucket** table;
    int size;
    int capacity;
    HashFunction hashFunction;
} HashTable;

// Hash function for string key (djb2 algorithm)
unsigned long hashString(const char* key) {
    unsigned long hash = 5412;
    const char* str = key;

    while (*str != '\0') {
        hash = ((hash << 5) + hash) + *str; // hash * 33 + c
        str++;
    }

    return hash;
}

// Hash function for integer keys
unsigned long hashInt(int key) {
    return key;
}

Bucket* bucketCreate(int key, void* value) {
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


HashTable* hashTableCreate(int capacity) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (ht != NULL) {
        ht->table = (Bucket**)malloc(sizeof(Bucket*) * capacity);
        ht->size = 0;
        ht->capacity = capacity;
        for (int i = 0; i < capacity; i++) ht->table[i] = NULL;
    }
    return ht;
}

// Get the value associated with the given key
const void* hashTableGet(HashTable* obj, int key) {
    unsigned long index = hashInt(key) % obj->capacity;
    Bucket* current = obj->table[index];

    // Traverse the linked list from start
    while (current != NULL) {
        if (current->key == key) return current->value; // key found, return value
        current = current->next;
    }
    return NULL; // key not found, return NULL
}

// Insert a key-value pair into the hash table
bool hashTableInsert(HashTable* obj, int key, void* value) {
    // hash table is full!
    // TODO: increase hashtable size to double, and re-hash all keys
    if (obj->size == obj->capacity) return false;

    // key is already in hash table!
    if (hashTableGet(obj, key) != NULL) return false;

    // Put the new key-value pair into hash table
    unsigned long index = hashInt(key) % obj->capacity;

    // Create a new key-value pair
    Bucket* new = bucketCreate(key, value);
    // Insert the new pair at the beginning of the linked list
    new->next = obj->table[index];
    obj->table[index] = new;

    obj->size++;

    return true;
}

// Remove the key-value pair from the hash table with given key
bool hashTableRemove(HashTable* obj, int key) {
    unsigned long index = hashInt(key) % obj->capacity;

    // Traverse the linked list from start
    Bucket* current = obj->table[index];
    Bucket* prev = NULL;
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) { // The key found in the first in the linked list
                obj->table[index] = current->next;
            } else { // The non-first to be removed in the linked list
                prev->next = current->next;
            }

            obj->size--;
            free(current);

            return true;
        }

        prev = current;
        current = current->next;
    }

    return false;
}

void hashTableFree(HashTable* obj) {
    for (int i = 0; i < obj->capacity; i++) {
        Bucket* current = obj->table[i];
        while (current != NULL) {
            Bucket* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(obj);
}

void printInt(void* value) {
    printf("%d] ", *((int*)value));
}

void hashTablePrint(HashTable* obj) {
    printf("HashTable, size: %d, capacity: %d, elements:\n", obj->size, obj->capacity);
    for (int i = 0; i < obj->capacity; i++) {
        Bucket* item = obj->table[i];
        if (item != NULL) {
            printf("index: %d: [key: %d, value: ", i, item->key);
            printInt(item->value);
            // if (item->next != NULL) printf("chaining value:");
            while (item->next != NULL) {
                printf("[key: %d, value: ", item->next->key);
                printInt(item->next->value);
                item = item->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}
#pragma endregion


struct Key {
    /* data */
};

typedef struct {
    int v1;
    char* v2;
} Value2;

void value2Free(void* data) {
    Value2 *temp = (Value2*)data;
    free(temp->v2);
    free(temp);
}

int main() {
    HashTable* ht = hashTableCreate(10);

    hashTableInsert(ht, 1, &(int){ 1 });
    hashTableInsert(ht, 2, &(int){ 2 });
    hashTableInsert(ht, 3, &(int){ 3 });
    hashTableInsert(ht, 4, &(int){ 4 });
    hashTableInsert(ht, 5, &(int){ 5 });
    hashTableInsert(ht, 6, &(int){ 6 });
    hashTableInsert(ht, 7, &(int){ 7 });
    hashTableInsert(ht, 8, &(int){ 8 });
    hashTableInsert(ht, 9, &(int){ 9 });
    // hashTableInsert(ht, 10, &(int){10});
    hashTableInsert(ht, 11, &(int){ 11 });

    hashTablePrint(ht);
    hashTableFree(ht);

    return 0;
}