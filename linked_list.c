#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

typedef struct LinkedListVal {
    intptr_t value;
    struct LinkedListVal *next;
} LinkedListVal;

typedef struct {
    LinkedListVal *head;
} LinkedList;

LinkedList *list_init() {
    LinkedList *k = malloc(sizeof(LinkedList));
    return k;
}

void list_push(LinkedList *l, int val) {
    LinkedListVal *el = malloc(sizeof(LinkedListVal));
    el->value = val;
    el->next = l->head;
    l->head = el;
}

int list_head(LinkedList *l) { return l->head->value; }

int list_pop(LinkedList *l) {
    LinkedListVal *el = l->head;
    l->head = el->next;
    int val = el->value;
    free(el);
    return val;
}

void list_print(LinkedList *l) {
    LinkedListVal *el = l->head;
    while (el) {
        printf("%lu\t", el->value);
        el = el->next;
    }
    printf("\n");
}

void list_collect(LinkedList *l) {
    while (l->head) {
        LinkedListVal *next = l->head->next;
        free(l->head);
        l->head = next;
    }
    free(l);
}

int main() {
    // LinkedList* l = list_init();
    // list_push(l, 1);
    // list_push(l, 2);
    // list_push(l, 3);
    // list_push(l, 4);
    // list_print(l);
    // list_collect(l);
    return 0;
}
