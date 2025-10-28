#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100000

typedef struct {
    int next;    
    char str[100];
} node;

int head;

void pushNode(node* nodes, int len, node* value, int idx) {
    if (idx == -1) {
        value->next = head;
        head = len;
    } else {
        int next = nodes[idx].next;
        nodes[idx].next = len;
        value->next = next;
    }

    printf("%d\n", len);
}

void popNode(node* nodes, int idx) {
    int id;

    if (idx == -1) {
        id = head;
        head = nodes[id].next;
    } else {
        id = nodes[idx].next;
        nodes[idx].next = nodes[id].next;
    }
    printf("%s\n", nodes[id].str);
}

void func(FILE* in) {
    int n, f, q;
    fscanf(in, "%d %d %d", &n, &f, &q);

    node* nodes = calloc(n + q, sizeof(node));
    head = f;

    for (int i = 0; i < n; i++) {
        fscanf(in, "%s %d", nodes[i].str, &nodes[i].next);
    }

    for (int i = 0; i < q; i++) {
        int mode;
        fscanf(in, "%d", &mode);
        if (!mode) {
            int idx;
            fscanf(in, "%d %s", &idx, nodes[n].str);
            pushNode(nodes, n, &nodes[n], idx);
            n++;
        } else {
            int idx;
            fscanf(in, "%d", &idx);
            popNode(nodes, idx);
        }
    }

    printf("===\n");

    for (int i = head; i != -1; i = nodes[i].next) {
        printf("%s\n", nodes[i].str);
    }

    printf("===\n");
    
    free(nodes);
}

int main() {
    int t;
    FILE* in = fopen("input.txt", "r");
    fscanf(in, "%d", &t);
    
    for (int i = 0; i < t; i++) {
        func(in);
    }

    return 0;
}