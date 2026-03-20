#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *edges;
    int *head;
    int *next;
    int count;
} Graph;

void add_edge(Graph *g, int u, int v) {
    g->edges[g->count] = v;
    g->next[g->count] = g->head[u];
    g->head[u] = g->count++;
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    int m;
    scanf("%d %d", &n, &m);

    Graph g;
    g.edges = malloc(m * sizeof(int));
    g.head = malloc((n + 1) * sizeof(int));
    g.next = malloc(m * sizeof(int));
    g.count = 0;

    for (int i = 1; i <= n; i++) {
        g.head[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(&g, u, v);
    }

    int* dist = malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) { 
        dist[i] = -1;
    }

    int* queue = malloc((n + 1) * sizeof(int));
    int head = 0;
    int tail = 0;

    dist[1] = 0;
    queue[tail++] = 1;

    while (head < tail) {
        int u = queue[head++];
        for (int i = g.head[u]; i != -1; i = g.next[i]) {
            int v = g.edges[i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                queue[tail++] = v;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d\n", dist[i]);
    }

    free(g.edges);
    free(g.head);
    free(g.next);
    free(dist);
    free(queue);

    return 0;
}