#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char grid[10][11];
char words[10][11];
int num_words = 0;
bool used[10];

bool can_place_h(int r, int c, int len, char* word) {
    if (strlen(word) != len) return false;
    for (int i = 0; i < len; i++) {
        if (grid[r][c + i] != '-' && grid[r][c + i] != word[i]) return false;
    }
    return true;
}

bool can_place_v(int r, int c, int len, char* word) {
    if (strlen(word) != len) return false;
    for (int i = 0; i < len; i++) {
        if (grid[r + i][c] != '-' && grid[r + i][c] != word[i]) return false;
    }
    return true;
}

bool solve() {
    int r = -1, c = -1;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j] == '-') {
                r = i; c = j;
                break;
            }
        }
        if (r != -1) break;
    }

    if (r == -1) return true;

    int start_c = c;
    while (start_c > 0 && grid[r][start_c - 1] != '+') start_c--;
    int len_h = 0;
    while (start_c + len_h < 10 && grid[r][start_c + len_h] != '+') len_h++;

    if (len_h > 1 && grid[r][c] == '-') {
        for (int i = 0; i < num_words; i++) {
            if (!used[i] && can_place_h(r, start_c, len_h, words[i])) {
                char prev[11];
                for (int j = 0; j < len_h; j++) {
                    prev[j] = grid[r][start_c + j];
                    grid[r][start_c + j] = words[i][j];
                }
                used[i] = true;
                if (solve()) return true;
                used[i] = false;
                for (int j = 0; j < len_h; j++) grid[r][start_c + j] = prev[j];
            }
        }
        return false;
    }

    int start_r = r;
    while (start_r > 0 && grid[start_r - 1][c] != '+') start_r--;
    int len_v = 0;
    while (start_r + len_v < 10 && grid[start_r + len_v][c] != '+') len_v++;

    if (len_v > 1 && grid[r][c] == '-') {
        for (int i = 0; i < num_words; i++) {
            if (!used[i] && can_place_v(start_r, c, len_v, words[i])) {
                char prev[11];
                for (int j = 0; j < len_v; j++) {
                    prev[j] = grid[start_r + j][c];
                    grid[start_r + j][c] = words[i][j];
                }
                used[i] = true;
                if (solve()) return true;
                used[i] = false;
                for (int j = 0; j < len_v; j++) grid[start_r + j][c] = prev[j];
            }
        }
        return false;
    }

    return false;
}

int main() {
    freopen("input.txt", "r", stdin);

    for (int i = 0; i < 10; i++) {
        scanf("%s", grid[i]);
    }

    char line[200];
    scanf("%s", line);
    char* token = strtok(line, ";");
    while (token != NULL) {
        strcpy(words[num_words++], token);
        token = strtok(NULL, ";");
    }

    solve();

    for (int i = 0; i < 10; i++) {
        printf("%s\n", grid[i]);
    }

    return 0;
}