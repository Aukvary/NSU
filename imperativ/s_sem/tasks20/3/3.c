#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 1e18

long long dist[301][301];
int next_node[301][301];

void print_path(int i, int j) {
    int count = 1;
    int curr = i;
    while (curr != j) {
        count++;
        curr = next_node[curr][j];
    }
    
    printf("%d", count);
    curr = i;
    while (curr != j) {
        printf(" %d", curr);
        curr = next_node[curr][j];
    }
    printf(" %d\n", j);
}

int main() {
    freopen("input.txt", "r", stdin);

    int n, m, p, k;
    scanf("%d %d %d %d", &n, &m, &p, &k);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = INT_MAX;
            next_node[i][j] = j;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        long long l;
        scanf("%d %d %lld", &u, &v, &l);
        if (l < dist[u][v]) {
            dist[u][v] = l;
            dist[v][u] = l;
        }
    }

    for (int mid = 1; mid <= n; mid++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][mid] == INT_MAX || dist[mid][j] == INT_MAX) continue;
                if (dist[i][j] > dist[i][mid] + dist[mid][j]) {
                    dist[i][j] = dist[i][mid] + dist[mid][j];
                    next_node[i][j] = next_node[i][mid];
                }
            }
        }
    }

    for (int i = 0; i < p; i++) {
        int s, t;
        scanf("%d %d", &s, &t);
        printf("%lld ", dist[s][t]);
        print_path(s, t);
    }

    for (int i = 0; i < k; i++) {
        int s, t;
        scanf("%d %d", &s, &t);
        printf("%lld\n", dist[s][t]);
    }

    return 0;
}