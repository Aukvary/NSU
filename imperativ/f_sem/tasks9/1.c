#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 1000001

typedef struct node {
    char str[8];
    struct node* next;
} node;

node* nodes[SIZE] = { NULL };

void pushNode(node* head, node* value) {
    node* cur = head;
    node* prev = NULL;

    while (cur != NULL) {
        prev = cur;
        cur = cur->next;
    }

    prev->next = value;
}

int main() {
    int n;
    FILE* in = fopen("input.txt", "r");
    fscanf(in, "%d", &n);

    for (int i = 0; i < n; i++) {
        node* n = malloc(sizeof(node));
        n->next = NULL;
        int idx;
        fscanf(in, "%d %s", &idx, n->str);
        if (nodes[idx] == NULL) {
            nodes[idx] = n;
        } else {
            pushNode(nodes[idx], n);
        }
    }

    for (int i = 0; i < SIZE; i++) {
        node* cur = nodes[i];

        while (cur != NULL) {
            printf("%d %s\n", i, cur->str);
            cur = cur->next;
        }
    }

    return 0;
}