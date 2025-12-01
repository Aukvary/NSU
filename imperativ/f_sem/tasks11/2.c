#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node;

typedef void (*callback)(void *ctx, int *value);

void arrayForeach(void *ctx, callback func, int *arr, int n) {
    for (int i = 0; i < n; i++) {
        func(ctx, &arr[i]);
    }
}

void listForeach(void* ctx, callback func, node* head) {
    node* cur = head;

    while (cur) {
        func(ctx, &cur->data);
        cur = cur->next;
    }
}

void sum(void* ctx, int* value) {
    if ((*value) % 2 != 0) return;
    *((int*)ctx) += *value;
}

int main() {
    freopen("input.txt", "r", stdin);
    int n;

    scanf("%d", &n);

    int* nums = calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    int s = 0;

    arrayForeach(&s, sum, nums, n);
    printf("%d ", s);
    node* nodes = calloc(n, sizeof(node));

    for (int i = 0; i < n - 1; i++) {
        nodes[i].next = &nodes[i + 1];
        nodes[i].data = nums[i];
    } 

    nodes[n - 1].data = nums[n - 1];

    s = 0;
    listForeach(&s, sum, &nodes[0]);

    printf("%d", s);

    return 0;
}