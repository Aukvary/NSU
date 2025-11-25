#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int tail;
    int head;

    int count;
    int capacity;

    int* data;
} loop_queue;

loop_queue new(int capacity) {
    return (loop_queue) {
        .tail = 0,
        .head = 0,

        .count = 0,
        .capacity = 1 + 2 * capacity,

        .data = calloc(1 + 2 * capacity, sizeof(int))
    };
}

void push_back(loop_queue* lq, int num) {
    lq->data[lq->tail] = num;
    lq->tail = (lq->tail + 1) % lq->capacity;
    lq->count++;
}

int pop_back(loop_queue* lq) {
    if (lq->count == 0) return 0;

    lq->tail = (lq->tail - 1 + lq->capacity) % lq->capacity;
    lq->count--;

    return lq->data[lq->tail];
}

void push_front(loop_queue* lq, int num) {
    lq->head = (lq->head - 1 + lq->capacity) % lq->capacity;
    lq->data[lq->head] = num;
    lq->count++;
}

int pop_front(loop_queue* lq) {
    if (lq->count == 0) return 0;

    int val = lq->data[lq->head];
    lq->head = (lq->head + 1) % lq->capacity;
    lq->count--;

    return val;
}

void print(loop_queue* lq) {
    printf("%d ", lq->count);

    int current = lq->head;
    for (int i = 0; i < lq->count; i++) {
        printf(" %d", lq->data[current]);
        current = (current + 1) % lq->capacity;
    }
    printf("\n");
}

int main() {
    int n;
    int m;
    FILE* in = fopen("input.txt", "r");
    fscanf(in, "%d %d", &n, &m);

    loop_queue left = new(n);
    loop_queue right = new(n);

    for (int i = 0; i < n; i++) {
        push_back(&left, i + 1);
        push_back(&right, -(i + 1));
    }

    char operations[m + 1];
    fscanf(in, "%s", operations);

    for (int i = 0; i < m; i++) {
        char ch_mode = operations[i];
        int mode;

        if (ch_mode >= '0' && ch_mode <= '9') {
            mode = ch_mode - '0';
        } else {
            mode = ch_mode - 'A' + 10;
        }

        loop_queue* lq = (mode & 8) ? &right : &left;

        if (lq->count == 0) continue;

        int card;
        if (mode & 4) {
            card = pop_back(lq);
        } else {
            card = pop_front(lq);
        }

        loop_queue* target = (mode & 2) ? &right : &left;

        if (mode & 1) {
            push_back(target, card);
        } else {
            push_front(target, card);
        }
    }

    print(&left);
    print(&right);

    free(left.data);
    free(right.data);

    return 0;
}
