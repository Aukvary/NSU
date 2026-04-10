#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100

int capacity[MAX_N + 1][MAX_N + 1] = {0};
int parent[MAX_N + 1] = {0};
int n;

int bfs(int s, int t) {
    int visited[MAX_N + 1] = {0};
    int queue[MAX_N];
    int front = 0, rear = 0;
    
    visited[s] = 1;
    queue[rear++] = s;
    parent[s] = -1;
    
    while (front < rear) {
        int u = queue[front++];
        
        for (int v = 1; v <= n; v++) {
            if (visited[v] || capacity[u][v] <= 0) continue;
            
            if (v == t) {
                parent[v] = u;
                return 1;
            }
            visited[v] = 1;
            parent[v] = u;
            queue[rear++] = v;
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    
    while (bfs(s, t)) {
        int path_flow = INT_MAX;
        
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            if (capacity[u][v] < path_flow) {
                path_flow = capacity[u][v];
            }
        }
        
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= path_flow;
            capacity[v][u] += path_flow;
        }
        
        flow += path_flow;
    }
    
    return flow;
}

int main() {
    freopen("input.txt", "r", stdin);

    int k;
    scanf("%d %d", &n, &k);
        
    for (int i = 0; i < k; i++) {
        int v, u, c;
        scanf("%d %d %d", &v, &u, &c);
        capacity[v][u] += c;
        capacity[u][v] += c;
    }
    
    int result = max_flow(1, n);
    printf("%d\n", result);
    
    return 0;
}