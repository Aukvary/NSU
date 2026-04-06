#include <stdio.h>
#include <stdlib.h>

#define INF 1e9

typedef struct edge {
    int to;
    int cap;
    int flow;
    int rev;
    int id;
} edge;

typedef struct graph {
    edge* data;
    int size;
    int cap;
} graph_t;

graph_t* g;
int* level;
int* ptr;
int n, m, o;

void add_edge(int from, int to, int cap, int id) {
    edge a = {to, cap, 0, g[to].size, id};
    edge b = {from, 0, 0, g[from].size, 0};
    if (g[from].size == g[from].cap) {
        g[from].cap = g[from].cap ? g[from].cap * 2 : 2;
        g[from].data = realloc(g[from].data, sizeof(edge) * g[from].cap);
    }
    g[from].data[g[from].size++] = a;
    if (g[to].size == g[to].cap) {
        g[to].cap = g[to].cap ? g[to].cap * 2 : 2;
        g[to].data = realloc(g[to].data, sizeof(edge) * g[to].cap);
    }
    g[to].data[g[to].size++] = b;
}

int bfs(int s, int t, int num_v) {
    for (int i = 0; i < num_v; i++) level[i] = -1;
    level[s] = 0;
    int* q = malloc(sizeof(int) * num_v);
    int head = 0, tail = 0;
    q[tail++] = s;
    while (head < tail) {
        int v = q[head++];
        for (int i = 0; i < g[v].size; i++) {
            if (g[v].data[i].cap - g[v].data[i].flow > 0 && level[g[v].data[i].to] == -1) {
                level[g[v].data[i].to] = level[v] + 1;
                q[tail++] = g[v].data[i].to;
            }
        }
    }
    free(q);
    return level[t] != -1;
}

int dfs(int v, int t, int pushed) {
    if (pushed == 0 || v == t) return pushed;
    for (int* i = &ptr[v]; *i < g[v].size; (*i)++) {
        edge* e = &g[v].data[*i];
        if (level[v] + 1 != level[e->to] || e->cap - e->flow == 0) continue;
        int tr = dfs(e->to, t, pushed < e->cap - e->flow ? pushed : e->cap - e->flow);
        if (tr == 0) continue;
        e->flow += tr;
        g[e->to].data[e->rev].flow -= tr;
        return tr;
    }
    return 0;
}

int main() {
    scanf("%d %d %d", &n, &m, &o);
    int s, t;
    scanf("%d %d", &s, &t);
    
    int num_v = 2 * n + 1;
    g = calloc(num_v, sizeof(graph_t));
    
    for (int i = 1; i <= n; i++) {
        int cap = (i == s || i == t) ? INF : 1;
        add_edge(i, i + n, cap, 0);
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u + n, v, 1, i);
        if (o == 0) add_edge(v + n, u, 1, i);
    }

    int flow = 0;
    level = malloc(sizeof(int) * num_v);
    ptr = malloc(sizeof(int) * num_v);
    while (bfs(s, t + n, num_v)) {
        for (int i = 0; i < num_v; i++) ptr[i] = 0;
        while (1) {
            int pushed = dfs(s, t + n, INF);
            if (pushed == 0) break;
            flow += pushed;
        }
    }

    printf("%d\n", flow);
    for (int k = 0; k < flow; k++) {
        int curr = s;
        int path[10000];
        int path_ids[10000];
        int path_to[10000];
        int p_idx = 0;
        
        while (curr != t) {
            int out_node = curr + n;
            for (int i = 0; i < g[out_node].size; i++) {
                edge* e = &g[out_node].data[i];
                if (e->id > 0 && e->flow == 1) {
                    path[p_idx] = curr;
                    path_ids[p_idx] = e->id;
                    path_to[p_idx] = e->to;
                    e->flow = 0; 
                    curr = e->to;
                    p_idx++;
                    break;
                }
            }
        }
        printf("%d\n", p_idx);
        for (int i = 0; i < p_idx; i++) {
            printf("%d %d %d\n", path[i], path_ids[i], path_to[i]);
        }
    }

    return 0;
}