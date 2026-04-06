#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 110
#define MAX_M 10000

typedef struct {
    int to;
    int cap;
    int flow;
    int rev;
} Edge;

typedef struct {
    int u;
    int v;
    int c;
} InputEdge;

int n;
int m;
int s;
int t;
InputEdge edges[MAX_M];
Edge* graph[MAX_N];
int edge_count[MAX_N];
int level[MAX_N], iter[MAX_N];

void add_edge(int from, int to, int cap) {
    Edge e1 = {to, cap, 0, edge_count[to]};
    Edge e2 = {from, 0, 0, edge_count[from]};
    
    graph[from] = realloc(graph[from], (edge_count[from] + 1) * sizeof(Edge));
    graph[to] = realloc(graph[to], (edge_count[to] + 1) * sizeof(Edge));
    
    graph[from][edge_count[from]++] = e1;
    graph[to][edge_count[to]++] = e2;
}

void bfs(int s) {
    int queue[MAX_N], front = 0, rear = 0;
    memset(level, -1, sizeof(level));
    level[s] = 0;
    queue[rear++] = s;
    
    while (front < rear) {
        int v = queue[front++];
        for (int i = 0; i < edge_count[v]; i++) {
            Edge e = graph[v][i];
            if (e.cap > e.flow && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                queue[rear++] = e.to;
            }
        }
    }
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (; iter[v] < edge_count[v]; iter[v]++) {
        Edge e = graph[v][iter[v]];
        if (e.cap > e.flow && level[v] < level[e.to]) {
            int d = dfs(e.to, t, (f < e.cap - e.flow) ? f : e.cap - e.flow);
            if (d > 0) {
                graph[v][iter[v]].flow += d;
                graph[e.to][e.rev].flow -= d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow() {
    int flow = 0, f;
    while (1) {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        while ((f = dfs(s, t, INT_MAX)) > 0) {
            flow += f;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    
    scanf("%d %d", &n, &m);
    scanf("%d %d", &s, &t);
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].c);
    }
    
    for (int i = 0; i < m; i++) {
        add_edge(edges[i].u, edges[i].v, edges[i].c);
        add_edge(edges[i].v, edges[i].u, edges[i].c);
    }
    
    int min_cut_value = max_flow();
    
    int visited[MAX_N] = {0};
    int queue[MAX_N], front = 0, rear = 0;
    visited[s] = 1;
    queue[rear++] = s;
    
    while (front < rear) {
        int v = queue[front++];
        for (int i = 0; i < edge_count[v]; i++) {
            Edge e = graph[v][i];
            if (e.cap > e.flow && !visited[e.to]) {
                visited[e.to] = 1;
                queue[rear++] = e.to;
            }
        }
    }
    
    int cut_edges[MAX_M], cut_cnt = 0;
    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v;
        if (visited[u] && !visited[v]) {
            cut_edges[cut_cnt++] = i;
        } else if (visited[v] && !visited[u]) {
            cut_edges[cut_cnt++] = i;
        }
    }
    
    printf("%d %d\n", min_cut_value, cut_cnt);
    for (int i = 0; i < cut_cnt; i++) {
        int idx = cut_edges[i];
        printf("%d %d\n", edges[idx].u, edges[idx].v);
    }
    
    for (int i = 1; i <= n; i++) {
        free(graph[i]);
    }
    
    return 0;
}