#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 1e18

typedef struct {
    int to;
    int weight;
    int id;
    int next;
} Edge;

typedef struct {
    long long dist;
    int u;
} Node;

Edge edges[200005] = {0};
int head[100005], edge_cnt = 0;
long long dist[100005] = {0};
int parent_edge[100005] = {0};
int parent_node[100005] = {0};
Node heap[1000005] = {0};
int heap_size = 0;

void add_edge(int u, int v, int w, int id) {
    edges[++edge_cnt] = (Edge){v, w, id, head[u]};
    head[u] = edge_cnt;
}

void push(long long d, int u) {
    heap[++heap_size] = (Node){d, u};
    int i = heap_size;
    while (i > 1 && heap[i].dist < heap[i / 2].dist) {
        Node temp = heap[i];
        heap[i] = heap[i / 2];
        heap[i / 2] = temp;
        i /= 2;
    }
}

Node pop() {
    Node res = heap[1];
    heap[1] = heap[heap_size--];
    int i = 1;
    while (i * 2 <= heap_size) {
        int j = i * 2;
        if (j + 1 <= heap_size && heap[j + 1].dist < heap[j].dist) j++;
        if (heap[i].dist <= heap[j].dist) break;
        Node temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
        i = j;
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin); 
    
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    int queries[20][2];
    for (int i = 0; i < K; i++) {
        scanf("%d %d", &queries[i][0], &queries[i][1]);
    }

    for (int i = 1; i <= M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w, i);
    }

    for (int q = 0; q < K; q++) {
        int start = queries[q][0];
        int end = queries[q][1];

        for (int i = 1; i <= N; i++) {
            dist[i] = INF;
            parent_edge[i] = -1;
        }

        dist[start] = 0;
        heap_size = 0;
        push(0, start);

        while (heap_size > 0) {
            Node top = pop();
            int u = top.u;
            if (top.dist > dist[u]) continue;
            if (u == end) break;

            for (int i = head[u]; i; i = edges[i].next) {
                int v = edges[i].to;
                if (dist[v] > dist[u] + edges[i].weight) {
                    dist[v] = dist[u] + edges[i].weight;
                    parent_node[v] = u;
                    parent_edge[v] = edges[i].id;
                    push(dist[v], v);
                }
            }
        }

        if (dist[end] == INF) {
            printf("DOOMED\n"); 
        } else {
            int path[200005], f = 0;
            int curr = end;
            while (curr != start) {
                path[f++] = parent_edge[curr];
                curr = parent_node[curr];
            }
            printf("quarantine %lld %d", dist[end], f); 
            for (int i = f - 1; i >= 0; i--) {
                printf(" %d", path[i]); 
            }
            printf("\n");
        }
    }

    return 0;
}