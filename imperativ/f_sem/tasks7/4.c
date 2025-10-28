#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data;
    
    int prev;
    int next;
} node;

int head;
int tail;  

void pushFront(node* nodes, int len, node* value, int idx) {
    if (idx == -1) {
        value->next = head;
        value->prev = -1;
        if (head != -1) {
            nodes[head].prev = len;
        } else {
            tail = len;  
        }
        head = len;
    } else {
        value->next = nodes[idx].next;
        value->prev = idx;
        if (nodes[idx].next != -1) {
            nodes[nodes[idx].next].prev = len;
        } else {
            tail = len;  
        }
        nodes[idx].next = len;
    }
    printf("%d\n", len);
}

void pushBack(node* nodes, int len, node* value, int idx) {
    if (idx == -1) {
        value->prev = tail;
        value->next = -1;
        if (tail != -1) {
            nodes[tail].next = len;
        } else {
            head = len;  
        }
        tail = len;
    } else {
        value->prev = nodes[idx].prev;
        value->next = idx;
        if (nodes[idx].prev != -1) {
            nodes[nodes[idx].prev].next = len;
        } else {
            head = len;  
        }
        nodes[idx].prev = len;
    }
    printf("%d\n", len);
}

void pop(node* nodes, int idx) {
    if (nodes[idx].prev != -1) {
        nodes[nodes[idx].prev].next = nodes[idx].next;
    } else {
        head = nodes[idx].next;  
    }
    
    if (nodes[idx].next != -1) {
        nodes[nodes[idx].next].prev = nodes[idx].prev;
    } else {
        tail = nodes[idx].prev;  
    }
    
    printf("%d\n", nodes[idx].data);
}

void func(FILE* in) {
    int n, f, l, q;  
    fscanf(in, "%d %d %d %d", &n, &f, &l, &q);  

    node* nodes = calloc(n + q, sizeof(node));
    head = f;
    tail = l;

    for (int i = 0; i < n; i++) {
        fscanf(in, "%d %d %d", &nodes[i].data, &nodes[i].next, &nodes[i].prev);  
    }

    for (int i = 0; i < q; i++) {
        int mode;
        fscanf(in, "%d", &mode);

        if (mode == 1) {
            int idx, value;
            fscanf(in, "%d %d", &idx, &value);
            nodes[n].data = value;
            pushFront(nodes, n, &nodes[n], idx);
            n++;
        } else if (mode == -1) {
            int idx, value;
            fscanf(in, "%d %d", &idx, &value);
            nodes[n].data = value;
            pushBack(nodes, n, &nodes[n], idx);
            n++;
        } else if (mode == 0) {
            int idx;
            fscanf(in, "%d", &idx);
            pop(nodes, idx);
        }
    }

    printf("===\n");
    for (int i = head; i != -1; i = nodes[i].next) {
        printf("%d\n", nodes[i].data);  
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

    fclose(in);
    return 0;
}