#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct Edge{
    int to;
    int id;
    struct Edge* next;
} Edge;

Edge** adj;
int* tin;
int* low;
int* visited;
int timer;

int* bridges;
int bridge_count = 0;

void add_edge(int u, int v, int id) {
    Edge* new_edge = malloc(sizeof(Edge));
    new_edge->to = v;
    new_edge->id = id;
    new_edge->next = adj[u];
    adj[u] = new_edge;
}

void dfs(int v, int p_id) {
    visited[v] = 1;
    tin[v] = low[v] = timer++;
    
    for (Edge* e = adj[v]; e != NULL; e = e->next) {
        if (e->id == p_id) continue; 
        
        if (visited[e->to]) {
            low[v] = MIN(low[v], tin[e->to]);
        } else {
            dfs(e->to, e->id);
            low[v] = MIN(low[v], low[e->to]);
            if (low[e->to] > tin[v]) {
                bridges[bridge_count++] = e->id;
            }
        }
    }
}

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    adj = calloc(n + 1, sizeof(Edge*));
    tin = malloc((n + 1) * sizeof(int));
    low = malloc((n + 1) * sizeof(int));
    visited = calloc(n + 1, sizeof(int));
    bridges = malloc(m * sizeof(int));

    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u == v) continue; 
        add_edge(u, v, i);
        add_edge(v, u, i);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, -1);
        }
    }

    
    qsort(bridges, bridge_count, sizeof(int), cmp);

    printf("%d\n", bridge_count);
    for (int i = 0; i < bridge_count; i++) {
        printf("%d%c", bridges[i], (i == bridge_count - 1 ? '\n' : ' '));
    }

    
    return 0;
}