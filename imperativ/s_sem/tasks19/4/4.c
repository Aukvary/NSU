#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    int adj[500][500];

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char line[501];
        scanf("%s", line);
        for (int j = 0; j < n; j++) {
            adj[i][j] = (line[j] == '1');
        }
        adj[i][i] = 1;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (!adj[i][k]) continue;
            for (int j = 0; j < n; j++) {
                if (!adj[k][j]) continue; 
                adj[i][j] = 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", adj[i][j]);
        }
        printf("\n");
    }

    return 0;
}