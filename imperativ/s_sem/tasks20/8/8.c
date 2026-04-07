#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 2e18

typedef struct Edge {
    int u, v;
    long long weight;
} Edge;

int main() {
    int n, m, start_node;
    scanf("%d %d %d", &n, &m, &start_node);

    Edge* edges = malloc(m * sizeof(Edge));
    for (int i = 0; i < m; i++) {
        scanf("%d %d %lld", &edges[i].u, &edges[i].v, &edges[i].weight);
    }

    long long* dist = malloc((n + 1) * sizeof(long long));
    bool* reachable = malloc((n + 1) * sizeof(bool));
    bool* negative_cycle = malloc((n + 1) * sizeof(bool));

    for (int i = 1; i <= n; i++) {
        dist[i] = (long long)INF;
        reachable[i] = false;
        negative_cycle[i] = false;
    }

    dist[start_node] = 0;
    reachable[start_node] = true;


    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dist[edges[j].u] >= INF) continue;
            if (dist[edges[j].v] > dist[edges[j].u] + edges[j].weight) {
                dist[edges[j].v] = dist[edges[j].u] + edges[j].weight;
            }
        }
    }


    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            if (dist[edges[j].u] >= INF) continue;
            if (dist[edges[j].v] > dist[edges[j].u] + edges[j].weight) {
                dist[edges[j].v] = dist[edges[j].u] + edges[j].weight;
                negative_cycle[edges[j].v] = true;
            }
        }
    }


    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            if (negative_cycle[edges[j].u]) {
                negative_cycle[edges[j].v] = true;
            }
        }
    }


    for (int i = 1; i <= n; i++) {
        if (dist[i] >= INF / 2) {
            printf("*\n");
        } else if (negative_cycle[i]) {
            printf("-\n");
        } else {
            printf("%lld\n", dist[i]);
        }
    }

    free(edges);
    free(dist);
    free(reachable);
    free(negative_cycle);

    return 0;
}