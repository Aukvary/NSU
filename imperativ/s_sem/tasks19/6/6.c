#include <stdio.h>
#include <stdlib.h>

#define SIZE_N 5001
#define SIZE_M 100001

typedef struct Node {
    int to;
    struct Node* next;
} Node;

Node* adj[SIZE_N];
int in_degree[SIZE_N];
int heap[SIZE_N];
int heap_ptr = 0;

void push(int val) {
    heap[++heap_ptr] = val;
    int cur = heap_ptr;
    while (cur > 1 && heap[cur] < heap[cur / 2]) {
        int tmp = heap[cur];
        heap[cur] = heap[cur / 2];
        heap[cur / 2] = tmp;
        cur /= 2;
    }
}

int pop() {
    int res = heap[1];
    heap[1] = heap[heap_ptr--];
    int cur = 1;
    while (cur * 2 <= heap_ptr) {
        int child = cur * 2;
        if (child + 1 <= heap_ptr && heap[child + 1] < heap[child]) {
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

void add_edge(int u, int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->to = v;
    newNode->next = adj[u];
    adj[u] = newNode;
    in_degree[v]++;
}

int main() {
    int n;
    int m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }

    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            push(i);
        }
    }

    int result[SIZE_N];
    int count = 0;

    while (heap_ptr > 0) {
        int u = pop();
        result[count++] = u;

        Node* cur = adj[u];
        while (cur) {
            int v = cur->to;
            in_degree[v]--;
            if (in_degree[v] == 0) push(v);
            cur = cur->next;
        }
    }

    if (count < n) {
        printf("bad course\n");
    } else {
        for (int i = 0; i < n; i++) {
            printf("%d%c", result[i], (i == n - 1 ? '\n' : ' '));
        }
    }

    return 0;
}