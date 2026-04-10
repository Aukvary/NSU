#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100005
#define MAX_M 200005

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* graph[SIZE] = {0};
int indeg[SIZE] = {0};
int topo[SIZE] = {0};
int value[SIZE] = {0};
int n;
int m;

void add_edge(int from, int to) {
    Edge* e = malloc(sizeof(Edge));
    e->to = to;
    e->next = graph[from];
    graph[from] = e;
    indeg[to]++;
}

void free_graph() {
    for (int i = 1; i <= n; i++) {
        Edge* e = graph[i];
        while (e) {
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }

    int queue[SIZE];
    int front = 0, rear = 0;

    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            queue[rear++] = i;
        }
    }

    int topo_index = 0;
    while (front < rear) {
        int u = queue[front++];
        topo[topo_index++] = u;

        for (Edge* e = graph[u]; e; e = e->next) {
            int v = e->to;
            if (--indeg[v] == 0) {
                queue[rear++] = v;
            }
        }
    }

    if (topo_index != n) {
        printf("NO\n");
        free_graph();
        return 0;
    }

    int cur = n;
    for (int i = n - 1; i >= 0; i--) {
        value[topo[i]] = cur--;
    }

    printf("YES\n");
    for (int i = 1; i <= n; i++) {
        printf("%d ", value[i]);
    }
    printf("\n");

    free_graph();
    return 0;
}