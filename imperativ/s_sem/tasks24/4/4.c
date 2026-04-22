#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int n, m;
int* head;
int* to;
int* next;
int edge_count;
int* best_path;
int best_len = 0;
int* current_path;
bool* visited;

void add_edge(int u, int v) {
    to[edge_count] = v;
    next[edge_count] = head[u];
    head[u] = edge_count++;
}

void find_path() {
    int curr = rand() % n + 1;
    int len = 0;
    
    for (int i = 1; i <= n; i++) visited[i] = false;

    while (true) {
        visited[curr] = true;
        current_path[len++] = curr;

        int neighbors[256];
        int count = 0;
        for (int i = head[curr]; i != -1; i = next[i]) {
            if (!visited[to[i]]) {
                if (count < 256) neighbors[count++] = to[i];
            }
        }

        if (count == 0) break;
        curr = neighbors[rand() % count];
    }

    if (len > best_len) {
        best_len = len;
        for (int i = 0; i < len; i++) best_path[i] = current_path[i];
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    scanf("%d %d", &n, &m);

    head = malloc((n + 1) * sizeof(int));
    visited = malloc((n + 1) * sizeof(bool));
    current_path = malloc((n + 1) * sizeof(int));
    best_path = malloc((n + 1) * sizeof(int));
    to = malloc((2 * m) * sizeof(int));
    next = malloc((2 * m) * sizeof(int));

    for (int i = 1; i <= n; i++) head[i] = -1;
    edge_count = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    srand(time(NULL));
    clock_t start_time = clock();
    
    while ((double)(clock() - start_time) / CLOCKS_PER_SEC < 0.9) {
        find_path();
        if (best_len == n) break;
    }

    printf("%d\n", best_len);
    for (int i = 0; i < best_len; i++) {
        printf("%d%c", best_path[i], i == best_len - 1 ? '\n' : ' ');
    }

    free(head);
    free(visited);
    free(current_path);
    free(best_path);
    free(to);
    free(next);

    return 0;
}