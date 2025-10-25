#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int next;
    char str[10];
} node;


int main() {
    int t;
    FILE* in = fopen("input.txt", "r");
    fscanf(in, "%d", &t);

    int n;
    int f;
    int q;

    fscanf(in, "%d %d %d", &n, &f, &q);

    node* nodes = calloc(n + q, sizeof(node));

    for (int i = 0; i < n; i++) {

    }

    return 0;
}