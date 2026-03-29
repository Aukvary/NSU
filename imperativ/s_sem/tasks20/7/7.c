#include <stdio.h>
#include <stdlib.h>

#define SIZE 100005
#define MIN(a, b) ((a) < (b) ? (a) : (b))


typedef struct Node {
    int to;
    struct Node* next;
} Node;

Node* adj[SIZE];
int tin[SIZE];
int low[SIZE];
int timer;
int is_articulation[SIZE];
int visited[SIZE];

void add_edge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->to = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

void dfs(int v, int p) {
    visited[v] = 1;
    tin[v] = low[v] = ++timer;
    int children = 0;
    
    for (Node* curr = adj[v]; curr != NULL; curr = curr->next) {
        int to = curr->to;
        if (to == p) continue;
        if (visited[to]) {
            low[v] = MIN(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = MIN(low[v], low[to]);
            if (low[to] >= tin[v] && p != -1) {
                is_articulation[v] = 1;
            }
            children++;
        }
    }
    if (p == -1 && children > 1) {
        is_articulation[v] = 1;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    
    int n;
    int m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u == v) continue;
        add_edge(u, v);
        add_edge(v, u);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, -1);
        }
    }

    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (is_articulation[i]) count++;
    }

    printf("%d\n", count);
    int first = 1;
    for (int i = 1; i <= n; i++) {
        if (is_articulation[i]) {
            if (!first) printf(" ");
            printf("%d", i);
            first = 0;
        }
    }

    return 0;
}