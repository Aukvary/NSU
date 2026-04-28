#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);

    int n, m;
    scanf("%d %d", &n, &m);

    int** a = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        a[i] = malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int is_nash = 1;

            for (int r = 0; r < n; r++) {
                if (r != i && a[i][j] >= a[r][j]) {
                    is_nash = 0;
                    break;
                }
            }

            if (!is_nash) continue;

            for (int c = 0; c < m; c++) {
                if (c != j && a[i][j] <= a[i][c]) {
                    is_nash = 0;
                    break;
                }
            }

            if (is_nash) {
                printf("%d %d\n", i + 1, j + 1);
                return 0;
            }
        }
    }

    printf("0 0\n");

    for (int i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);

    return 0;
}