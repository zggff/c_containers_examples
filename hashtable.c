#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#define CAPACITY 10
#define MAX_LEN 20

typedef struct hash_item {
    char key[MAX_LEN];
    size_t value;
    struct hash_item *next;
} hash_item;

typedef struct {
    hash_item *inner[CAPACITY];
    size_t size;
} hashtable;

size_t hash_function(char *str);
void ht_print(hashtable *hs);
void ht_insert(hashtable *hs, char *key, size_t value);
size_t *ht_get(hashtable *hs, char *key);
void ht_remove(hashtable *hs, char *key);
void ht_set(hashtable *hs, char *key, size_t value);

size_t hash_function(char *str) {
    size_t result = 0;
    size_t len = strnlen(str, MAX_LEN);
    for (size_t i = 0; i < len; i++) {
        result += str[i];
        result = (result * i) % CAPACITY;
    }
    return result;
}

void ht_print(hashtable *hs) {
    for (int i = 0; i < CAPACITY; i++) {
        if (hs->inner[i] == NULL) {
            printf("%i\t---\n", i);
        } else {
            printf("%i", i);
            hash_item *next = hs->inner[i];
            while (next != NULL) {
                printf("\t%s: %zu\n", next->key, next->value);
                next = next->next;
            }
        }
    }
}

void ht_insert(hashtable *hs, char *key, size_t value) {
    size_t hash = hash_function(key);
    size_t len = strnlen(key, MAX_LEN);
    hash_item *tmp = (hash_item *)malloc(sizeof(hash_item));
    strncpy(tmp->key, key, len);
    tmp->value = value;
    tmp->next = hs->inner[hash];
    hs->inner[hash] = tmp;
}

size_t *ht_get(hashtable *hs, char *key) {
    size_t hash = hash_function(key);
    size_t len = strnlen(key, MAX_LEN);
    hash_item *tmp = hs->inner[hash];
    while (tmp != NULL) {
        if (strncmp(tmp->key, key, len) == 0) {
            return &tmp->value;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void ht_remove(hashtable *hs, char *key) {
    size_t hash = hash_function(key);
    size_t len = strnlen(key, MAX_LEN);
    hash_item *tmp = hs->inner[hash];
    hash_item *prev = NULL;
    while (tmp != NULL && strncmp(tmp->key, key, len) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        return;
    }
    if (prev == NULL) {
        hs->inner[hash] = tmp->next;
    } else {
        prev->next = tmp->next;
    }
    free(tmp);
}

void ht_set(hashtable *hs, char *key, size_t value) {
    size_t *tmp = ht_get(hs, key);
    if (tmp != NULL) {
        (*tmp) = value;
    } else {
        ht_insert(hs, key, value);
    }
}

int main() {
    hashtable hs = {0};
    ht_insert(&hs, "Jacob", 12);
    ht_insert(&hs, "zggff", 69);
    ht_print(&hs);
    printf("\n\n");
    ht_set(&hs, "Jacob", 420);
    ht_print(&hs);
    printf("\n\n");
    ht_set(&hs, "2317", 2317);
    ht_print(&hs);

    return 0;
}
