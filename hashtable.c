#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#define CAPACITY 10
#define MAX_LEN 20

size_t hash_function(char *str) {
    size_t result = 0;
    size_t len = strnlen(str, MAX_LEN);
    for (size_t i = 0; i < len; i++) {
        result += str[i];
        result = (result * i) % CAPACITY;
    }
    return result;
}

typedef struct hash_item {
    char key[MAX_LEN];
    int value;
    struct hash_item *next;
} hash_item;

typedef struct {
    hash_item *inner[CAPACITY];
    size_t size;
} hashtable;

void hashtable_print(hashtable *hs) {
    for (int i = 0; i < CAPACITY; i++) {
        if (hs->inner[i] == NULL) {
            printf("%i\t---\n", i);
        } else {
            printf("%i", i);
            hash_item *next = hs->inner[i];
            while (next != NULL) {
                printf("\t%s: %i\n", next->key, next->value);
                next = next->next;
            }
        }
    }
}

void hashtable_insert(hashtable *hs, char *key, int value) {
    size_t hash = hash_function(key);
    size_t len = strnlen(key, MAX_LEN);
    hash_item *tmp = (hash_item *)malloc(sizeof(hash_item));
    strncpy(tmp->key, key, len);
    tmp->value = value;
    tmp->next = hs->inner[hash];
    hs->inner[hash] = tmp;
}

int *hashtable_get(hashtable *hs, char *key) {
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

void hashtable_remove(hashtable *hs, char *key) {
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

void hashtable_set(hashtable *hs, char *key, int value) {
    int *tmp = hashtable_get(hs, key);
    if (tmp != NULL) {
        (*tmp) = value;
    } else {
        hashtable_insert(hs, key, value);
    }
}

int main() {
    hashtable hs = {0};
    hashtable_insert(&hs, "Jacob", 12);
    hashtable_insert(&hs, "zggff", 69);
    hashtable_print(&hs);
    printf("\n\n");
    hashtable_set(&hs, "Jacob", 420);
    hashtable_print(&hs);
    printf("\n\n");
    hashtable_set(&hs, "2317", 2317);
    hashtable_print(&hs);

    return 0;
}
