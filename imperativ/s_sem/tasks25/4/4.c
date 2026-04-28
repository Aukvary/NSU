#include <stdio.h>
#include <stdlib.h>

#define B 256

typedef struct Block {
    int data[B];
    int size;
    struct Block* prev;
} Block;

typedef struct {
    Block* last;
} Stack;

Stack* create_stack() {
    Stack* st = malloc(sizeof(Stack));
    st->last = NULL;
    return st;
}

void push(Stack* st, int x) {
    if (st->last == NULL || st->last->size == B) {
        Block* nb = malloc(sizeof(Block));
        nb->size = 0;
        nb->prev = st->last;
        st->last = nb;
    }
    st->last->data[st->last->size++] = x;
}

int top(Stack* st) {
    return st->last->data[st->last->size - 1];
}

int pop(Stack* st) {
    int val = st->last->data[st->last->size - 1];
    st->last->size--;
    if (st->last->size == 0) {
        Block* t = st->last;
        st->last = t->prev;
        free(t);
    }
    return val;
}

int main() {
    int Q;
    scanf("%d", &Q);

    Stack* st = create_stack();

    char op[8];
    int x;

    for (int i = 0; i < Q; i++) {
        scanf("%s", op);
        if (op[0] == '+') {
            scanf("%d", &x);
            push(st, x);
        } else if (op[0] == '-') {
            printf("%d\n", pop(st));
        } else {
            printf("%d\n", top(st));
        }
    }

    return 0;
}