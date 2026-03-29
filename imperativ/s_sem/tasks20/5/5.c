#include <stdio.h>
#include <stdlib.h>

#define SIZE 100005

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* adj[SIZE] = {0};
Edge* rev_adj[SIZE] = {0};
int visited[SIZE] = {0};
int order[SIZE] = {0};
int component[SIZE] = {0};
int order_ptr = 0;
int component_count = 0;

void add_edge(Edge** list, int u, int v) {
    Edge* new_edge = malloc(sizeof(Edge));
    new_edge->to = v;
    new_edge->next = list[u];
    list[u] = new_edge;
}

void dfs1(int u) {
    visited[u] = 1;
    for (Edge* e = adj[u]; e != NULL; e = e->next) {
        if (!visited[e->to]) {
            dfs1(e->to);
        }
    }
    order[order_ptr++] = u;
}

void dfs2(int u, int c) {
    component[u] = c;
    for (Edge* e = rev_adj[u]; e != NULL; e = e->next) {
        if (component[e->to] == 0) {
            dfs2(e->to, c);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u == v) continue; 
        add_edge(adj, u, v);
        add_edge(rev_adj, v, u);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        if (component[u] == 0) {
            component_count++;
            dfs2(u, component_count);
        }
    }

    printf("%d\n", component_count);
    for (int i = 1; i <= n; i++) {
        printf("%d%c", component[i], (i == n ? '\n' : ' '));
    }

    return 0;
}