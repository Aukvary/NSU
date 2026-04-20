#include <stdio.h>
#include <stdbool.h>

int graph[10][10];
int colors[10];
int V_count, E_count, m_colors;

bool is_safe(int v_idx, int c) {
    for (int i = 0; i < V_count; i++) {
        if (graph[v_idx][i] && c == colors[i]) {
            return false;
        }
    }
    return true;
}

bool solve(int v_idx) {
    if (v_idx == V_count) {
        return true;
    }

    for (int c = 1; c <= m_colors; c++) {
        if (is_safe(v_idx, c)) {
            colors[v_idx] = c;
            if (solve(v_idx + 1)) {
                return true;
            }
            colors[v_idx] = 0;
        }
    }
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);

    if (scanf("%d %d", &m_colors, &V_count) != 2) return 0;

    for (int i = 0; i < V_count; i++) {
        for (int j = 0; j < V_count; j++) {
            graph[i][j] = 0;
        }
        colors[i] = 0;
    }

    int u_edge, v_edge;
    while (scanf("%1d%1d", &u_edge, &v_edge) == 2) {
        if (u_edge < V_count && v_edge < V_count) {
            graph[u_edge][v_edge] = 1;
            graph[v_edge][u_edge] = 1;
        }
    }

    if (solve(0)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}