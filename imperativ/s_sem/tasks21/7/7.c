#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 3000
#define MAXM 10000

typedef struct {
    int to, rev, cap;
    int edge_id; 
} Edge;

typedef struct {
    int u, v, id;
} OEdge;

Edge *graph[MAXN + 1];
int graph_size[MAXN + 1];
int graph_capacity[MAXN + 1];
int level[MAXN + 1];
int iter[MAXN + 1];
int parent[MAXN + 1];
int parent_edge_id[MAXN + 1];
int parent_rev[MAXN + 1];

int N, M, O;
int s, t;

OEdge edges[MAXM + 1];
int edge_used[MAXM + 1];

void add_edge(int from, int to, int cap, int edge_id) {
    Edge e1 = {to, graph_size[to], cap, edge_id};
    Edge e2 = {from, graph_size[from], 0, -1}; 
    if (graph[from] == NULL) {
        graph[from] = (Edge*)malloc(sizeof(Edge) * 2);
        graph_capacity[from] = 2;
    }
    if (graph_size[from] >= graph_capacity[from]) {
        graph_capacity[from] *= 2;
        graph[from] = (Edge*)realloc(graph[from], sizeof(Edge) * graph_capacity[from]);
    }
    graph[from][graph_size[from]++] = e1;
    if (graph[to] == NULL) {
        graph[to] = (Edge*)malloc(sizeof(Edge) * 2);
        graph_capacity[to] = 2;
    }
    if (graph_size[to] >= graph_capacity[to]) {
        graph_capacity[to] *= 2;
        graph[to] = (Edge*)realloc(graph[to], sizeof(Edge) * graph_capacity[to]);
    }
    graph[to][graph_size[to]++] = e2;
}

int bfs() {
    memset(level, -1, sizeof(level));
    int queue[MAXN + 1];
    int head = 0, tail = 0;
    level[s] = 0;
    queue[tail++] = s;
    while (head < tail) {
        int v = queue[head++];
        for (int i = 0; i < graph_size[v]; i++) {
            Edge *e = &graph[v][i];
            if (e->cap > 0 && level[e->to] < 0) {
                level[e->to] = level[v] + 1;
                queue[tail++] = e->to;
            }
        }
    }
    return level[t] != -1;
}

int dfs(int v, int f, int *flow_found) {
    if (v == t) {
        *flow_found = 1;
        return f;
    }
    for (int i = iter[v]; i < graph_size[v]; i++) {
        Edge *e = &graph[v][i];
        if (e->cap > 0 && level[v] < level[e->to]) {
            int d = dfs(e->to, (f < e->cap ? f : e->cap), flow_found);
            if (*flow_found) {
                e->cap -= d;
                graph[e->to][e->rev].cap += d;
                return d;
            }
        }
        iter[v]++;
    }
    return 0;
}

int max_flow() {
    int flow = 0;
    while (bfs()) {
        memset(iter, 0, sizeof(iter));
        int flow_found;
        do {
            flow_found = 0;
            int f = dfs(s, INT_MAX, &flow_found);
            if (flow_found) {
                flow += f;
            }
        } while (flow_found);
    }
    return flow;
}

void find_paths() {
    int flow = max_flow();
    printf("%d\n", flow);
    
    for (int p = 0; p < flow; p++) {
        memset(parent, -1, sizeof(parent));
        memset(parent_edge_id, -1, sizeof(parent_edge_id));
        memset(parent_rev, -1, sizeof(parent_rev));
        int queue[MAXN + 1];
        int head = 0, tail = 0;
        queue[tail++] = s;
        parent[s] = s;
        while (head < tail) {
            int v = queue[head++];
            for (int i = 0; i < graph_size[v]; i++) {
                Edge *e = &graph[v][i];
                if (e->cap == 0 && e->edge_id != -1 && parent[e->to] == -1 && e->to != s) {
                    parent[e->to] = v;
                    parent_edge_id[e->to] = e->edge_id;
                    parent_rev[e->to] = i;
                    queue[tail++] = e->to;
                    if (e->to == t) break;
                }
            }
        }
        int path_edges[MAXM];
        int path_len = 0;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            path_edges[path_len++] = parent_edge_id[cur];
            for (int i = 0; i < graph_size[prev]; i++) {
                if (graph[prev][i].edge_id == parent_edge_id[cur]) {
                    graph[prev][i].cap = -1; 
                    break;
                }
            }
            cur = prev;
        }
        printf("%d\n", path_len);
        for (int i = path_len - 1; i >= 0; i--) {
            int eid = path_edges[i];
            if (O == 0) {
                if (edges[eid].u == parent[ (i == 0 ? t : (i == path_len-1 ? s : parent[path_edges[i-1]]) ) ]) {
                    printf("%d %d %d\n", edges[eid].u, eid, edges[eid].v);
                } else {
                    printf("%d %d %d\n", edges[eid].v, eid, edges[eid].u);
                }
            } else {
                printf("%d %d %d\n", edges[eid].u, eid, edges[eid].v);
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    
    scanf("%d %d %d", &N, &M, &O);
    scanf("%d %d", &s, &t);
    
    for (int i = 1; i <= N; i++) {
        graph[i] = NULL;
        graph_size[i] = 0;
        graph_capacity[i] = 0;
    }
    
    for (int i = 1; i <= M; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        edges[i].u = a;
        edges[i].v = b;
        edges[i].id = i;
        if (O == 0) {
            add_edge(a, b, 1, i);
            add_edge(b, a, 1, i);
        } else {
            add_edge(a, b, 1, i);
        }
    }
    
    find_paths();
    
    for (int i = 1; i <= N; i++) {
        free(graph[i]);
    }
    
    return 0;
}