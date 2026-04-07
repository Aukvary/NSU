#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long i64;

typedef struct {
    int to, rev;
    i64 cap;
} Edge;

typedef struct {
    Edge *data;
    int size, capacity;
} Vector;

Vector *graph;
int *distance, *pointer, *queue;
int node_count;

void add_directed_edge(int from, int to, i64 capacity) {
    if (graph[from].size == graph[from].capacity) {
        graph[from].capacity = graph[from].capacity ? graph[from].capacity * 2 : 4;
        graph[from].data = realloc(graph[from].data, graph[from].capacity * sizeof(Edge));
    }
    graph[from].data[graph[from].size++] = (Edge){to, graph[to].size, capacity};
}

void add_edge(int from, int to, i64 capacity) {
    add_directed_edge(from, to, capacity);
    add_directed_edge(to, from, 0);
}

void add_undirected_cut_edge(int u, int v, i64 weight) {
    add_edge(u, v, weight);
    add_edge(v, u, weight);
}

int breadth_first_search(int source, int sink) {
    memset(distance, -1, node_count * sizeof(int));
    int head = 0, tail = 0;
    queue[tail++] = source;
    distance[source] = 0;
    while (head < tail) {
        int vertex = queue[head++];
        for (int i = 0; i < graph[vertex].size; i++) {
            Edge *e = &graph[vertex].data[i];
            if (e->cap > 0 && distance[e->to] == -1) {
                distance[e->to] = distance[vertex] + 1;
                queue[tail++] = e->to;
            }
        }
    }
    return distance[sink] != -1;
}

i64 depth_first_search(int vertex, int sink, i64 flow) {
    if (vertex == sink) return flow;
    for (int *p = &pointer[vertex]; *p < graph[vertex].size; (*p)++) {
        Edge *e = &graph[vertex].data[*p];
        if (e->cap > 0 && distance[e->to] == distance[vertex] + 1) {
            i64 pushed = depth_first_search(e->to, sink, flow < e->cap ? flow : e->cap);
            if (pushed) {
                e->cap -= pushed;
                graph[e->to].data[e->rev].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

i64 dinic(int source, int sink) {
    i64 total_flow = 0, infinite = (i64)4e18;
    while (breadth_first_search(source, sink)) {
        memset(pointer, 0, node_count * sizeof(int));
        while (1) {
            i64 pushed = depth_first_search(source, sink, infinite);
            if (!pushed) break;
            total_flow += pushed;
        }
    }
    return total_flow;
}

void mark_reachable(int source, int *visited) {
    int head = 0, tail = 0;
    memset(visited, 0, node_count * sizeof(int));
    queue[tail++] = source;
    visited[source] = 1;
    while (head < tail) {
        int vertex = queue[head++];
        for (int i = 0; i < graph[vertex].size; i++) {
            Edge *e = &graph[vertex].data[i];
            if (e->cap > 0 && !visited[e->to]) {
                visited[e->to] = 1;
                queue[tail++] = e->to;
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int height, width;
    scanf("%d%d", &height, &width);
    int total_cells = height * width;
    i64 *first_value = (i64*)malloc(total_cells * sizeof(i64));
    i64 *second_value = (i64*)malloc(total_cells * sizeof(i64));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int idx = i * width + j;
            scanf("%lld%lld", &first_value[idx], &second_value[idx]);
        }
    }

    int source = total_cells, sink = total_cells + 1;
    node_count = total_cells + 2;
    graph = calloc(node_count, sizeof(Vector));
    distance = malloc(node_count * sizeof(int));
    pointer = malloc(node_count * sizeof(int));
    queue = malloc(node_count * sizeof(int));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int idx = i * width + j;
            i64 cost0, cost1;
            if (((i + j) & 1) == 0) {
                cost0 = first_value[idx];
                cost1 = second_value[idx];
            } else {
                cost0 = second_value[idx];
                cost1 = first_value[idx];
            }
            add_edge(source, idx, cost1);
            add_edge(idx, sink, cost0);
        }
    }

    int extra_edges;
    scanf("%d", &extra_edges);
    i64 penalty_sum = 0;

    for (int k = 0; k < extra_edges; k++) {
        int row1, col1, row2, col2;
        i64 penalty;
        scanf("%d%d%d%d%lld", &row1, &col1, &row2, &col2, &penalty);
        --row1; --col1; --row2; --col2;
        int u = row1 * width + col1;
        int v = row2 * width + col2;
        add_undirected_cut_edge(u, v, penalty);
        penalty_sum += penalty;
    }

    i64 min_cut = dinic(source, sink);
    i64 result = min_cut - penalty_sum;
    printf("%lld\n", result);

    int *visited = (int*)malloc(node_count * sizeof(int));
    mark_reachable(source, visited);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int idx = i * width + j;
            int side = visited[idx] ? 0 : 1;
            int output = (((i + j) & 1) == 0) ? side : (1 - side);
            putchar('0' + output);
        }
        putchar('\n');
    }

    return 0;
}