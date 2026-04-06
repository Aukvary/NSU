#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE_N 105

int a, b, m;
int g[SIZE_N][SIZE_N] = {0};
int matchU[SIZE_N]; 
int matchV[SIZE_N]; 
int used[SIZE_N];   

int dfs(int u) {
    for (int v = 1; v <= b; v++) {
        if (!g[u][v] || used[v]) continue;

        used[v] = 1;
        if (matchV[v] == -1 || dfs(matchV[v])) {
            matchU[u] = v;
            matchV[v] = u;
            return 1;
        }
    }
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);

    scanf("%d %d %d", &a, &b, &m);
    
    memset(matchU, -1, sizeof(matchU));
    memset(matchV, -1, sizeof(matchV));
    
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        g[x][y] = 1;
    }
    
    int result = 0;
    for (int u = 1; u <= a; u++) {
        memset(used, 0, sizeof(used));
        if (dfs(u)) {
            result++;
        }
    }
    
    printf("%d\n", result);
    for (int u = 1; u <= a; u++) {
        if (matchU[u] != -1) {
            printf("%d %d\n", u, matchU[u]);
        }
    }
    
    return 0;
}