#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 2000000000000000LL 

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

Edge* adj[5001];
long long dist[5001];
int parent[5001];
int friends[51];
bool in_queue[5001];
int queue[1000000]; 

void add_edge(int u, int v, int w) {
    Edge* new_edge = malloc(sizeof(Edge));
    new_edge->to = v;
    new_edge->weight = w;
    new_edge->next = adj[u];
    adj[u] = new_edge;
}

void print_path(int v) {
    if (v == -1) return;
    print_path(parent[v]);
    printf(" %d", v);
}

int count_path(int v) {
    int count = 0;
    while (v != -1) {
        count++;
        v = parent[v];
    }
    return count;
}

int main() {
    freopen("input.txt", "r", stdin);

    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < k; i++) {
        scanf("%d", &friends[i]);
    }

    for (int i = 1; i <= n; i++) adj[i] = NULL;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }

    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        parent[i] = -1;
        in_queue[i] = false;
    }

    dist[1] = 0;
    int head = 0, tail = 0;
    queue[tail++] = 1;
    in_queue[1] = true;

    while (head < tail) {
        int u = queue[head++];
        in_queue[u] = false;

        for (Edge* e = adj[u]; e != NULL; e = e->next) {
            if (dist[u] + e->weight >= dist[e->to]) continue;
            
            dist[e->to] = dist[u] + e->weight;
            parent[e->to] = u;
            if (!in_queue[e->to]) {
                queue[tail++] = e->to;
                in_queue[e->to] = true;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        int target = friends[i];
        printf("%lld %d", dist[target], count_path(target));
        print_path(target);
        printf("\n");
    }

    return 0;
}