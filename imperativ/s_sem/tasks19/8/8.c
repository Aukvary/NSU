#include <stdio.h>
#include <stdlib.h>

#define SIZE 100001

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* adj[SIZE];
int in_degree[SIZE];
int heap[SIZE];
int heap_size = 0;
int res[SIZE];

void push(int val) {
    heap[++heap_size] = val;
    int cur = heap_size;
    while (cur > 1 && heap[cur] < heap[cur / 2]) {
        int tmp = heap[cur];
        heap[cur] = heap[cur / 2];
        heap[cur / 2] = tmp;
        cur /= 2;
    }
}

int pop() {
    int res = heap[1];
    heap[1] = heap[heap_size--];
    int cur = 1;
    while (cur * 2 <= heap_size) {
        int child = cur * 2;
        if (child + 1 <= heap_size && heap[child + 1] < heap[child]) {
            child++;
        }

        if (heap[cur] <= heap[child]) {
            break;
        }

        int tmp = heap[cur];
        heap[cur] = heap[child];
        heap[child] = tmp;
        cur = child;
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    int m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) break;
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = v;
        newNode->next = adj[u];
        adj[u] = newNode;
        in_degree[v]++;
    }

    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            push(i);
        }
    }

    int count = 0;
    while (heap_size > 0) {
        int u = pop();
        res[count++] = u;

        Node* cur = adj[u];
        while (cur) {
            int v = cur->data;
            in_degree[v]--;
            if (in_degree[v] == 0) {
                push(v);
            }
            Node* temp = cur;
            cur = cur->next;
            free(temp);
        }
    }

    if (count < n) {
        printf("bad course\n");
    } else {
        for (int i = 0; i < n; i++) {
            printf("%d%s", res[i], (i == n - 1 ? "" : " "));
        }
        printf("\n");
    }

    return 0;
}