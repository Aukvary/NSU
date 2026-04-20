#include <stdio.h>
#include <stdbool.h>

int grid[9][9];
int rows[9], cols[9], boxes[9];

int get_box(int r, int c) {
    return (r / 3) * 3 + (c / 3);
}

void toggle_num(int r, int c, int num) {
    int mask = 1 << num;
    rows[r] ^= mask;
    cols[c] ^= mask;
    boxes[get_box(r, c)] ^= mask;
}

bool solve() {
    int r = -1, c = -1;
    int min_choices = 10;
    int best_mask = 0;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) {
                int mask = ~(rows[i] | cols[j] | boxes[get_box(i, j)]) & 0x3FE;
                int choices = 0;
                for (int m = mask; m > 0; m &= (m - 1)) choices++;

                if (choices == 0) return false;
                if (choices < min_choices) {
                    min_choices = choices;
                    r = i; c = j;
                    best_mask = mask;
                    if (min_choices == 1) goto found;
                }
            }
        }
    }

found:
    if (r == -1) return true;

    for (int num = 1; num <= 9; num++) {
        if (best_mask & (1 << num)) {
            grid[r][c] = num;
            toggle_num(r, c, num);
            if (solve()) return true;
            toggle_num(r, c, num);
            grid[r][c] = 0;
        }
    }
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    if (scanf("%d", &n) != 1) return 0;

    while (n--) {
        for (int i = 0; i < 9; i++) {
            rows[i] = cols[i] = boxes[i] = 0;
        }

        for (int i = 0; i < 9; i++) {
            char line[11];
            scanf("%s", line);
            for (int j = 0; j < 9; j++) {
                if (line[j] == '.') {
                    grid[i][j] = 0;
                } else {
                    int num = line[j] - '0';
                    grid[i][j] = num;
                    toggle_num(i, j, num);
                }
            }
        }

        if (solve()) {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    printf("%d", grid[i][j]);
                }
                printf("\n");
            }
        }
        if (n > 0) printf("\n");
    }
    return 0;
}