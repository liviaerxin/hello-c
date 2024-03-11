/*
 * File: lru_cache.c
 * Project: c
 * Created Date: Mon Mar 11 2024
 * Author: Frank
 * Last Modified: Mon Mar 11 2024
 * Modified By: Frank
 *
 * Implement the LRUCache class:
    - LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
    - int get(int key) Return the value of the key if the key exists, otherwise return -1.
    - void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to
 the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
 * The functions get and put must each run in O(1) average time complexity.
 *
 * Example:
    LRUCache lRUCache = new LRUCache(2);
    lRUCache.put(1, 1); // cache is {1=1}
    lRUCache.put(2, 2); // cache is {1=1, 2=2}
    lRUCache.get(1);    // return 1
    lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    lRUCache.get(2);    // returns -1 (not found)
    lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    lRUCache.get(1);    // return -1 (not found)
    lRUCache.get(3);    // return 3
    lRUCache.get(4);    // return 4
 */
// https://www.w3resource.com/c-programming-exercises/hash/c-hash-exercises-9.php
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 10
#define uint unsigned int

typedef struct Bucket {
    int key;
    void* value;
    struct Bucket* next;
} Bucket;

typedef struct {
    Bucket** table;
    int size;
    int capacity;
} HashTable;

/* Hash Table */
uint hashKey(int key) {
    return key;
}

Bucket* itemCreate(int key, void* value) {
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

bool hashTableContain(HashTable* obj, int key) {
    uint hashkey = hashKey(key) % obj->capacity;
    Bucket* item = obj->table[hashkey];
    while (item != NULL) {
        if (item->key == key) return true;
        item = item->next;
    }
    return false;
}

Bucket* hashTableGet(HashTable* obj, int key) {
    uint hashkey = hashKey(key) % obj->capacity;
    Bucket* item = obj->table[hashkey];
    while (item != NULL) {
        if (item->key == key) return item;
        item = item->next;
    }
    return NULL;
}

bool hashTableInsert(HashTable* obj, int key, void* value) {
    // hash table is full!
    if (obj->size == obj->capacity) return false;

    // key is already in hash table!
    if (hashTableContain(obj, key)) return false;

    uint hashkey = hashKey(key) % obj->capacity;

    // Put the new in the first.
    Bucket* new = itemCreate(key, value);
    new->next = obj->table[hashkey];
    obj->table[hashkey] = new;
    obj->size++;

    return true;
}

bool hashTablePut(HashTable* obj, int key, void* value) {
    // key is already in hash table!
    uint hashkey = hashKey(key) % obj->capacity;

    Bucket* existed = hashTableGet(obj, key);
    if (existed != NULL) {
        // Update key-value pair
        existed->value = value;
    } else {
        // hash table is full!
        if (obj->size == obj->capacity) return false;

        // Put the new in the first.
        Bucket* new = itemCreate(key, value);
        new->next = obj->table[hashkey];
        obj->table[hashkey] = new;
        obj->size++;
    }

    return true;
}

bool hashTableRemove(HashTable* obj, int key) {
    uint hashkey = hashKey(key) % obj->capacity;
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
            bucketFree(item);
            obj->size--;
            return true;
        }

        prev = item;
        item = item->next;
    }
    return false;
}

void bucketFree(Bucket* bucket) {
    // free when value is allocated in heap!
    free(bucket->value);
    free(bucket);
}

void hashTableFree(HashTable* obj) {
    for (int i = 0; i < obj->capacity; i++) {
        Bucket* item = obj->table[i];
        while (item != NULL) {
            Bucket* next = item->next;
            bucketFree(item);
            item = next;
        }
    }
    free(obj);
}

/* Hash Table */


typedef struct {
    HashTable* ht;
    Bucket* head;
    Bucket* tail;
    int size;
    int capacity;
} LRUCache;


LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->ht = hashTableCreate(capacity);
    cache->head = NULL;
    cache->tail = NULL;
    cache->size = 0;
    cache->capacity = capacity;
}

int lRUCacheGet(LRUCache* obj, int key) {
}

void lRUCachePut(LRUCache* obj, int key, int value) {
}

void lRUCacheFree(LRUCache* obj) {
    hashTableFree(obj->ht);
    obj->head = NULL;
    obj->tail = NULL;
}

int main() {
    return 0;
}