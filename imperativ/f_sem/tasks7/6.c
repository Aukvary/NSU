#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    double data;

    struct node* prev;
    struct node* next;
} node;

node* head;

double* initList() {
    node* n = malloc(sizeof(node));
    head = n;

    n->prev = NULL;
    n->next = NULL;

    n->data = 0;

    return &n->data;
}

double* getNext(double* curr) {
    node* n = (node*)curr;

    return &n->next->data;
}

double* getPrev(double* curr) {
    node* n = (node*)curr;

    return &n->prev->data;
}

double* addAfter(double* where, double newVal) {
    node* n = (node*)where;

    node* newN = malloc(sizeof(node));
}

void freeList(node* h) {
    node* cur = h;

    while (cur) {
        node* temp = cur->next;
        free(cur);
        cur = h;
    }
}