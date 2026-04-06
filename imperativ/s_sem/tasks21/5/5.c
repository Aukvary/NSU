#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 1e16

typedef struct Edge {
    int to;
    long long capacity;
    long long flow;
    int rev;
} Edge;

Edge* adj[160005];
int adj_size[160005];
int adj_cap[160005];
int level[160005];
int ptr[160005];
int queue[160005];

void add_edge(int from, int to, long long cap) {
    if (adj_size[from] == adj_cap[from]) {
        adj_cap[from] = (adj_cap[from] == 0) ? 4 : adj_cap[from] * 2;
        adj[from] = (Edge*)realloc(adj[from], adj_cap[from] * sizeof(Edge));
    }
    if (adj_size[to] == adj_cap[to]) {
        adj_cap[to] = (adj_cap[to] == 0) ? 4 : adj_cap[to] * 2;
        adj[to] = (Edge*)realloc(adj[to], adj_cap[to] * sizeof(Edge));
    }
    Edge e1 = {to, cap, 0, adj_size[to]};
    Edge e2 = {from, 0, 0, adj_size[from]};
    adj[from][adj_size[from]++] = e1;
    adj[to][adj_size[to]++] = e2;
}

bool bfs(int s, int t, int n) {
    for (int i = 0; i <= n; i++) level[i] = -1;
    level[s] = 0;
    int head = 0, tail = 0;
    queue[tail++] = s;
    while (head < tail) {
        int v = queue[head++];
        for (int i = 0; i < adj_size[v]; i++) {
            Edge *e = &adj[v][i];
            if (e->capacity - e->flow > 0 && level[e->to] == -1) {
                level[e->to] = level[v] + 1;
                queue[tail++] = e->to;
            }
        }
    }
    return level[t] != -1;
}

long long dfs(int v, int t, long long pushed) {
    if (pushed == 0 || v == t) return pushed;
    for (; ptr[v] < adj_size[v]; ptr[v]++) {
        Edge *e = &adj[v][ptr[v]];
        if (level[v] + 1 != level[e->to] || e->capacity - e->flow <= 0) continue;
        long long tr = dfs(e->to, t, pushed < e->capacity - e->flow ? pushed : e->capacity - e->flow);
        if (tr == 0) continue;
        e->flow += tr;
        adj[e->to][e->rev].flow -= tr;
        return tr;
    }
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);

    int h, w;
    scanf("%d %d", &h, &w);

    int s = 0, t = h * w + 1;
    long long sum_a = 0;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            long long a, b;
            scanf("%lld %lld", &a, &b);
            sum_a += a;
            int v = i * w + j + 1;
            add_edge(s, v, a);
            add_edge(v, t, b);
        }
    }

    int m;
    scanf("%d", &m);
    for (int k = 0; k < m; k++) {
        int r1, c1, r2, c2;
        long long p;
        scanf("%d %d %d %d %lld", &r1, &c1, &r2, &c2, &p);
        int u = (r1 - 1) * w + (c1 - 1) + 1;
        int v = (r2 - 1) * w + (c2 - 1) + 1;
        add_edge(u, v, p);
        add_edge(v, u, p);
    }

    long long flow = 0;
    while (bfs(s, t, t)) {
        for (int i = 0; i <= t; i++) ptr[i] = 0;
        long long pushed;
        while ((pushed = dfs(s, t, INF)) != 0) {
            flow += pushed;
        }
    }

    printf("%lld\n", flow - sum_a);

    bfs(s, t, t);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            printf("%d", level[i * w + j + 1] != -1 ? 1 : 0);
        }
        printf("\n");
    }

    return 0;
}