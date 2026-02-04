#include <stdio.h>

#define SIZE 200

int n;
char target[SIZE][SIZE] = {0};
char grid[SIZE][SIZE] = {0};
char click[SIZE][SIZE] = {0};
int clicks_count = 0;

void toggle(int r, int c) {
    grid[r][c] ^= 1;
    if (r > 1) grid[r-1][c] ^= 1;
    if (r < n) grid[r+1][c] ^= 1;
    if (c > 1) grid[r][c-1] ^= 1;
    if (c < n) grid[r][c+1] ^= 1;
}

void solve() {
    clicks_count = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                grid[i][j] = target[i][j];
            }
        }
        
        for (int j = 1; j <= n; j++) {
            if (mask & (1 << (j-1))) {
                click[1][j] = 1;
                toggle(1, j);
            }
        }
        
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (grid[i-1][j]) {
                    click[i][j] = 1;
                    toggle(i, j);
                }
            }
        }
        
        char ok = 1;
        for (int j = 1; j <= n; j++) {
            if (grid[n][j]) {
                ok = 0;
                break;
            }
        }
        
        if (ok) {
            clicks_count = 0;
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (click[i][j]) {
                        clicks_count++;
                    }
                }
            }
            return;
        }
    }
}

int main(void) {
    freopen("input.txt", "r", stdin);
    
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        char row[SIZE];
        scanf("%s", row);
        for (int j = 1; j <= n; j++) {
            target[i][j] = (row[j-1] == '*');
        }
    }
    
    solve();
    
    printf("%d\n", clicks_count);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (click[i][j]) {
                printf("%d %d\n", i, j);
            }
        }
    }
    
    return 0;
}