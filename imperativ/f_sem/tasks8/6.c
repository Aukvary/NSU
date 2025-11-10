#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int num;
    
    struct node* next;
    struct node* prev;
} node;

int main() {
    FILE* in = fopen("input.txt", "r");
    int n, k;
    fscanf(in, "%d %d", &n, &k);
    fclose(in);

    node* nodes = calloc(n, sizeof(node));
    
    for (int i = 0; i < n; i++) {
        nodes[i].num = i + 1;
        nodes[i].next = &nodes[(i + 1) % n];
        nodes[i].prev = &nodes[(i - 1 + n) % n];
    }

    node* cur = &nodes[0];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k - 1; j++) {
            cur = cur->next;
        }
        
        printf("%d\n", cur->num);
        
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        
        cur = cur->next;
    }
    
    free(nodes);
    return 0;
}