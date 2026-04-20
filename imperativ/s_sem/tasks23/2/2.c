#include <stdio.h>
#include <string.h>

int n, k, m, l;
int switches[10][10][100];
int current_voltage[100];
int solution[10];

int solve(int remote_idx) {
    if (remote_idx == n) {
        for (int i = 0; i < m; i++) {
            if (current_voltage[i] != l) return 0;
        }
        return 1;
    }

    int rem = n - remote_idx;

    for (int sw_idx = 0; sw_idx < k; sw_idx++) {
        int possible = 1;
        
        for (int i = 0; i < m; i++) {
            int next_v = current_voltage[i] + switches[remote_idx][sw_idx][i];
            if (next_v > l || next_v + (rem - 1) < l) {
                possible = 0;
                break;
            }
        }

        if (possible) {
            for (int i = 0; i < m; i++) current_voltage[i] += switches[remote_idx][sw_idx][i];
            solution[remote_idx] = sw_idx + 1;
            if (solve(remote_idx + 1)) return 1;
            for (int i = 0; i < m; i++) current_voltage[i] -= switches[remote_idx][sw_idx][i];
        }
    }
    return 0;
}

int main() {
    scanf("%d %d %d %d", &n, &k, &m, &l);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            char row[105];
            scanf("%s", row);
            for (int t = 0; t < m; t++) {
                switches[i][j][t] = (row[t] == 'X' ? 1 : 0);
            }
        }
    }

    memset(current_voltage, 0, sizeof(current_voltage));

    if (solve(0)) {
        printf("YES\n");
        for (int i = 0; i < n; i++) {
            printf("%d\n", solution[i]);
        }
    } else {
        printf("NO\n");
    }

    return 0;
}