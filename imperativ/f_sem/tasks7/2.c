#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100000

typedef struct {
    int next;
    char str[100];
} node;

node* newNode(int next, const char* str) {
    node* new = malloc(sizeof(node));

    new->next = next;
    strcpy(new->str, str);

    return new;
}

void pushNode(node** nodes, int* len, node* value, int idx) {
    
}

void popNode(node** nodes, int len,  int idx) {
    node* node = nodes[idx];

}



void func(FILE* in) {
    int n;
    int f;
    int q;

    fscanf(in, "%d %d %d", &n, &f, &q);

    node* nodes = calloc(n + q, sizeof(node));

    for (int i = 0; i < n; i++) {
        
    }
}


int main() {
    int t;
    FILE* in = fopen("input.txt", "r");
    fscanf(in, "%d", &t);

    return 0;
}