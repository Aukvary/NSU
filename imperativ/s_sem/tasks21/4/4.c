#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define SIZE_N 3000
#define SIZE_M 300000

typedef struct {
    int to;
    int weight;
    int next;
} Edge;

typedef struct {
    int node;
    int dist;
} Info;

Edge edges[SIZE_M * 2];
int head[SIZE_N + 1];
int edge_count = 0;

int dist[SIZE_N + 1];
int prev_node[SIZE_N + 1];
int visited[SIZE_N + 1];

Info heap[SIZE_N * 2];
int heap_size = 0;

void add_edge(int u, int v, int w) {
    edges[edge_count].to = v;
    edges[edge_count].weight = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
    
    edges[edge_count].to = u;
    edges[edge_count].weight = w;
    edges[edge_count].next = head[v];
    head[v] = edge_count++;
}

void swap(Info *a, Info *b) {
    Info temp = *a;
    *a = *b;
    *b = temp;
}

void push_heap(int node, int d) {
    int idx = heap_size++;
    heap[idx].node = node;
    heap[idx].dist = d;
    
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[parent].dist <= heap[idx].dist) break;
        swap(&heap[parent], &heap[idx]);
        idx = parent;
    }
}

Info pop_heap() {
    Info min = heap[0];
    heap[0] = heap[--heap_size];
    
    int idx = 0;
    while (1) {
        int left = idx * 2 + 1;
        int right = idx * 2 + 2;
        int smallest = idx;
        
        if (left < heap_size && heap[left].dist < heap[smallest].dist)
            smallest = left;
        if (right < heap_size && heap[right].dist < heap[smallest].dist)
            smallest = right;
        if (smallest == idx) break;
        
        swap(&heap[idx], &heap[smallest]);
        idx = smallest;
    }
    return min;
}

int is_empty() {
    return heap_size == 0;
}

void dijkstra(int start, int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        prev_node[i] = -1;
        visited[i] = 0;
    }
    heap_size = 0;
    
    dist[start] = 0;
    push_heap(start, 0);
    
    while (!is_empty()) {
        Info current = pop_heap();
        int u = current.node;
        
        if (visited[u]) continue;
        visited[u] = 1;
        
        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            int w = edges[e].weight;
            
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev_node[v] = u;
                push_heap(v, dist[v]);
            }
        }
    }
}

void print_path(int s, int t, int path[], int *path_len) {
    if (t == -1 || (s != t && prev_node[t] == -1)) {
        *path_len = 0;
        return;
    }
    
    int stack[SIZE_N];
    int top = 0;
    int cur = t;
    
    while (cur != -1) {
        stack[top++] = cur;
        if (cur == s) break;
        cur = prev_node[cur];
    }
    
    *path_len = 0;
    for (int i = top - 1; i >= 0; i--) {
        path[(*path_len)++] = stack[i];
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    int queries[20][2];
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &queries[i][0], &queries[i][1]);
    }
    
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }
    
    for (int q = 0; q < k; q++) {
        int s = queries[q][0];
        int t = queries[q][1];
        
        dijkstra(s, n);
        
        if (dist[t] == INT_MAX) {
            printf("NO\n");
        } else {
            int path[SIZE_N];
            int path_len;
            print_path(s, t, path, &path_len);
            
            printf("YES %d %d", dist[t], path_len);
            for (int i = 0; i < path_len; i++) {
                printf(" %d", path[i]);
            }
            printf("\n");
        }
    }
    
    return 0;
}