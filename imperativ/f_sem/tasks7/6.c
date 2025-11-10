#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#pragma pack(push, 1)
typedef struct node {
    double value;
    struct node* prev;
    struct node* next;
} node;
#pragma pack(pop)

double* initList() {
    node *head = malloc(sizeof(node));

    head->prev = head;
    head->next = head;

    head->value = 0.0;
    return &(head->value);
}

node* get(double *pval) {
    return (node*)(pval);
}

double *getNext(double *curr_val) {
    node *curr = get(curr_val);

    return &(curr->next->value);
}

double *getPrev(double *curr_val) {
    node *curr = get(curr_val);

    return &(curr->prev->value);
}

double *addAfter(double *where_val, double newval) {
    node *where = get(where_val);
    
    node *n = (node*)malloc(sizeof(node));
    n->value = newval;
    n->next = where->next;
    n->prev = where;

    where->next->prev = n;
    where->next = n;

    return &(n->value);
}

double *addBefore(double *where_val, double newval) {
    node *where = get(where_val);
    node *n = (node*)malloc(sizeof(node));
    
    n->value = newval;
    n->prev = where->prev;
    n->next = where;
    
    where->prev->next = n;
    where->prev = n;
    
    return &(n->value);
}

void erase(double *what_val) {
    node *what = get(what_val);

    what->prev->next = what->next;
    what->next->prev = what->prev;
    
    free(what);
}

void freeList(double *head_val) {
    node *head = get(head_val);
    node *cur = head->next;

    while (cur != head) {
        node *tmp = cur->next;
        free(cur);
        cur = tmp;
    }

    free(head);
}

void func(FILE* in) {
    int q;
    fscanf(in, "%d", &q);
    double* head = initList();
    double** nodes = calloc(q, sizeof(double*));
    int count = 0;

    for (int i = 0; i < q; ++i) {
        int type, idx;
        fscanf(in, "%d %d", &type, &idx);

        if (type == 1) {
            double val;
            fscanf(in, "%lf", &val);
            double* where = (idx == -1 ? head : nodes[idx]);
            nodes[count] = addAfter(where, val);
            count++;
        } else if (type == -1) {
            double val;
            fscanf(in, "%lf", &val);
            double* where = (idx == -1 ? head : nodes[idx]);
            nodes[count] = addBefore(where, val);
            count++;
        } else if (type == 0) {
            double *what = nodes[idx];
            printf("%0.3lf\n", *what);
            erase(what);
        }
    }

    printf("===\n");

    double* cur = getNext(head);
    while (cur != head) {
        printf("%0.3lf\n", *cur);
        cur = getNext(cur);
    }
    printf("===\n");

    free(nodes);
    freeList(head);
}

int main() {
    FILE* in = fopen("input.txt", "r");

    int t;
    fscanf(in, "%d", &t);
    for (int i = 0; i < t; i++) {
        func(in);
    }

    return 0;
}
