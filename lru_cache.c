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

#pragma region HashTable

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
    Bucket* new = bucketCreate(key, value);
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
        Bucket* new = bucketCreate(key, value);
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
    // free(bucket->value);
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

// 3 <-prev- 2 -next- >1
// 3(head) <- 2 <- 1 <- 0(tail)
// tail is the least recently used; head is the most recently used;
/*
when `put(1)`:
if 1 in cache:
    update key value pair
    1(head) <- 3 <- 2 <- 0(tail)

when `put(4, 4)`:
if cache size < capacity:
    4(head) <- 3 <- 2 <- 1 <- 0(tail)
else:
    evict(tail)
    4(head) <- 3 <- 2 <- 1(tail)

when `get(1)`:
1(head) <- 3 <- 2 <- 0(tail)

*/
typedef struct {
    HashTable* ht;
    Bucket* head;
    Bucket* tail;
    int size;
    int capacity;
} LRUCache;

typedef struct {
    int value;
    Bucket* prev;
    Bucket* next;
} IntValue;

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->ht = hashTableCreate(capacity);
    cache->head = NULL;
    cache->tail = NULL;
    cache->size = 0;
    cache->capacity = capacity;
    return cache;
}

int lRUCacheGet(LRUCache* obj, int key) {
    Bucket* current = hashTableGet(obj->ht, key);
    // If key is already in cache
    if (current != NULL) {
        // Update key in double linked list: move it to the head.

        // If at the tail
        if (((IntValue*)current->value)->next == NULL) {
            Bucket* new_tail = ((IntValue*)current->value)->prev;
            // If there are more than 2 buckets
            if (new_tail != NULL) {
                ((IntValue*)new_tail->value)->next = NULL;
                obj->tail = new_tail;
                Bucket* old_head = obj->head;
                ((IntValue*)old_head->value)->prev = current;
                ((IntValue*)current->value)->next = old_head;
                ((IntValue*)current->value)->prev = NULL;

                obj->head = current;
            }

        }
        // If at the head
        else if (((IntValue*)current->value)->prev == NULL) {
            // DO nothing
        }
        // If at the middle
        else {
            Bucket* prev = ((IntValue*)current->value)->prev;
            Bucket* next = ((IntValue*)current->value)->next;
            ((IntValue*)prev->value)->next = next;
            ((IntValue*)next->value)->prev = prev;

            Bucket* old_head = obj->head;
            ((IntValue*)old_head->value)->prev = current;
            ((IntValue*)current->value)->next = old_head;
            ((IntValue*)current->value)->prev = NULL;

            obj->head = current;
        }
        return ((IntValue*)current->value)->value;
    } else {
        return -1;
    }
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    int existed = lRUCacheGet(obj, key);

    // If key is already in cache
    if (existed > 0) {
        Bucket* current = hashTableGet(obj->ht, key);
        // Update value
        ((IntValue*)current->value)->value = value;
    }
    // If key is not in cache
    else {
        //  If cache is full, evict the tail bucket firstly.
        if (obj->size == obj->capacity) {
            Bucket* temp = obj->tail;
            Bucket* new_tail = ((IntValue*)temp->value)->prev;
            
            // If there are more than 2 buckets
            if (new_tail != NULL) {
                ((IntValue*)new_tail->value)->next = NULL;
                obj->tail = new_tail;
            }
            // If there one bucket
            else {
                obj->tail = NULL;
                obj->head = NULL;
            }


            hashTableRemove(obj->ht, temp->key);
            obj->size--;
        }

        // Insert into hashtable
        IntValue* wrap_val = (IntValue*)malloc(sizeof(IntValue));
        wrap_val->value = value;
        wrap_val->prev = NULL;
        wrap_val->next = obj->head;

        hashTableInsert(obj->ht, key, (void*)wrap_val);

        Bucket* current = hashTableGet(obj->ht, key);

        // Update head
        // If cache is empty
        if (obj->head == NULL) {
            obj->head = current;
            obj->tail = current;
        } else {
            ((IntValue*)obj->head->value)->prev = current;
            obj->head = current;
        }
        obj->size++;
    }
}

void lRUCacheFree(LRUCache* obj) {
    hashTableFree(obj->ht);
    // obj->head = NULL;
    // obj->tail = NULL;
}

void lRUCachePrint(LRUCache* obj) {
    printf("LRUCache, size: %d, capacity: %d, elements:\n", obj->size, obj->capacity);

    Bucket* current = obj->head;
    // if (current != NULL) printf("%p", current->value);
    while (current != NULL) {
        printf("[key: %d, value: ", current->key);
        printInt(current->value);
        current = ((IntValue*)current->value)->next;
    }
    printf("\n");
}

int main() {
    // HashTable* ht = hashTableCreate(10);

    // hashTableInsert(ht, 1, &(int){ 1 });
    // hashTableInsert(ht, 2, &(int){ 2 });
    // hashTableInsert(ht, 3, &(int){ 3 });
    // hashTableInsert(ht, 4, &(int){ 4 });
    // hashTableInsert(ht, 5, &(int){ 5 });
    // hashTableInsert(ht, 6, &(int){ 6 });
    // hashTableInsert(ht, 7, &(int){ 7 });
    // hashTableInsert(ht, 8, &(int){ 8 });
    // hashTableInsert(ht, 9, &(int){ 9 });
    // // hashTableInsert(ht, 10, &(int){10});
    // hashTableInsert(ht, 11, &(int){ 11 });

    // hashTablePrint(ht);
    // hashTableFree(ht);

    LRUCache* lRUCache = lRUCacheCreate(3000);
    lRUCachePut(lRUCache, 596,2980); // cache is {1=1}
    lRUCachePut(lRUCache, 2, 2); // cache is {1=1, 2=2}
    lRUCacheGet(lRUCache, 1);    // return 1
    lRUCachePut(lRUCache, 3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    lRUCacheGet(lRUCache, 2);    // returns -1 (not found)
    lRUCachePut(lRUCache, 4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    lRUCacheGet(lRUCache, 1);    // return -1 (not found)
    lRUCacheGet(lRUCache, 3);    // return 3
    lRUCacheGet(lRUCache, 4);    // return 4

    // hashTablePrint(lRUCache->ht);
    lRUCachePrint(lRUCache);
    lRUCacheFree(lRUCache);
    return 0;
}