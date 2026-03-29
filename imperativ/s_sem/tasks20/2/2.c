#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200005

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* graph[SIZE];
int color[SIZE]; 
int parent[SIZE];
int cycle_start, cycle_end;

void addEdge(int u, int v) {
    Edge* newEdge = malloc(sizeof(Edge));
    newEdge->to = v;
    newEdge->next = graph[u];
    graph[u] = newEdge;
}

int dfs(int v) {
    color[v] = 1; 
    Edge* cur = graph[v];
    while (cur != NULL) {
        int to = cur->to;
        if (color[to] == 0) {
            parent[to] = v;
            if (dfs(to)) return 1;
        } else if (color[to] == 1) {
            cycle_start = to;
            cycle_end = v;
            return 1;
        }
        cur = cur->next;
    }
    color[v] = 2; 
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);

    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        graph[i] = NULL;
        color[i] = 0;
        parent[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    cycle_start = -1;
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0 && dfs(i)) {
            break;
        }
    }

    if (cycle_start == -1) {
        printf("-1\n");
    } else {
        int cycle[SIZE];
        int count = 0;
        
        int v = cycle_end;
        while (v != cycle_start) {
            cycle[count++] = v;
            v = parent[v];
        }
        cycle[count++] = cycle_start;
        
        printf("%d\n", count);
        for (int i = count - 1; i >= 0; i--) {
            printf("%d ", cycle[i]);
        }
        printf("\n");
    }

    for (int i = 1; i <= n; i++) {
        Edge* cur = graph[i];
        while (cur != NULL) {
            Edge* temp = cur;
            cur = cur->next;
            free(temp);
        }
    }

    return 0;
}