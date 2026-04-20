#include <stdio.h>
#include <stdbool.h>

int m, n;
char grid[15][15];
int queen_pos[15];

bool is_safe(int row, int col) {
    for (int i = 0; i < row; i++) {
        int prev_col = queen_pos[i];
        if (prev_col == col || 
            (row - i) == (col - prev_col) || 
            (row - i) == (prev_col - col)) {
            return false;
        }
    }
    return true;
}

bool solve(int row) {
    if (row == m) {
        return true;
    }

    for (int col = 0; col < n; col++) {
        if (grid[row][col] == '?' && is_safe(row, col)) {
            queen_pos[row] = col;
            if (solve(row + 1)) return true;
        }
    }
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);

    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++) {
        scanf("%s", grid[i]);
    }

    if (solve(0)) {
        printf("YES\n");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (queen_pos[i] == j) {
                    printf("X");
                } else {
                    printf(".");
                }
            }
            printf("\n");
        }
    } else {
        printf("NO\n");
    }

    return 0;
}