#include <stdio.h>
#include <stdlib.h>

#define VALUE_TYPE int

typedef struct {
    size_t xorLinks;
    VALUE_TYPE data;
} node;

typedef struct {
    node* head;
    node* tail;
} list;

void initList(list* l) {
    node* h = malloc(sizeof(node));
    node* t = malloc(sizeof(node));

    h->xorLinks = (size_t)t ^ (size_t)t;  
    t->xorLinks = (size_t)h ^ (size_t)h;  

    *l = (list) {
        .head = h,
        .tail = t
    };
}

node* addBetween(node* r, node* l, VALUE_TYPE val) {
    node* n = malloc(sizeof(node));

    *n = (node){
        .xorLinks = (size_t)l ^ (size_t)r,
        .data = val
    };

    r->xorLinks ^= (size_t)l;
    r->xorLinks ^= (size_t)n;

    l->xorLinks ^= (size_t)r;
    l->xorLinks ^= (size_t)n;

    return n;
}

VALUE_TYPE eraseLeft(node* l, node* r) {
    size_t link = (size_t)l->xorLinks ^ (size_t)r;

    node* rr = (node*)link;

    rr->xorLinks ^= (size_t)l;
    rr->xorLinks ^= (size_t)r;

    r->xorLinks ^= (size_t)l;
    r->xorLinks ^= link;

    return l->data;
}

VALUE_TYPE eraseRight(node* l, node* r) {
    size_t link = (size_t)r->xorLinks ^ (size_t)l;

    node* ll = (node*)link;

    ll->xorLinks ^= (size_t)r;
    ll->xorLinks ^= (size_t)l;
    
    l->xorLinks ^= (size_t)r;
    l->xorLinks ^= link;

    return r->data;
}

void func(FILE* in) {
    int n;
    fscanf(in, "%d", &n);  

    node** nodes = calloc(n, sizeof(node*));
    
    list list_data;
    initList(&list_data);

    int len = 0;

    while (n--) {
        int mode;
        int l;
        int r;

        fscanf(in, "%d %d %d", &mode, &l, &r);

        node* left = l == -1 ? list_data.head : nodes[l];
        node* right = r == -1 ? list_data.tail : nodes[r];

        if (mode == -1) {
            eraseLeft(left, right);
        } else if (mode == 0) {
            VALUE_TYPE data;
            fscanf(in, "%d", &data);
            nodes[len++] = addBetween(left, right, data);
        } else {
            eraseRight(left, right);
        }
    }

    node* prev = list_data.head;
    node* cur = (node*)((size_t)list_data.head->xorLinks ^ (size_t)list_data.tail);

    while (cur != list_data.tail) {
        printf("%d\n", cur->data);  
        node* temp = cur;
        cur = (node*)((size_t)cur->xorLinks ^ (size_t)prev);
        prev = temp;
    }

    printf("===\n"); 

    for (int i = 0; i < len; i++) {
        free(nodes[i]);
    }

    free(nodes);
    free(list_data.head);
    free(list_data.tail);
}

int main() {
    FILE* in = fopen("input.txt", "r");

    int t;
    fscanf(in, "%d", &t);
    
    while (t--) {
        func(in);
    }

    fclose(in);
    return 0;
}