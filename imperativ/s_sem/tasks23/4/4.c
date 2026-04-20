#include <stdio.h>
#include <string.h>

#define MOD 1000000007

long long dp[2][1 << 18];
int grid[25][10];
int n, m;

void solve() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        char row[15];
        scanf("%s", row);
        for (int j = 0; j < m; j++) {
            grid[i][j] = (row[j] == '#');
        }
    }

    int states = 1 << (2 * m);
    int cur = 0;
    memset(dp[cur], 0, sizeof(dp[cur]));
    dp[cur][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int next = cur ^ 1;
            memset(dp[next], 0, sizeof(dp[next]));
            for (int mask = 0; mask < states; mask++) {
                if (!dp[cur][mask]) continue;
                long long val = dp[cur][mask];
                int s = (mask >> (2 * j)) & 3;
                int nmask = mask & ~(3 << (2 * j));

                if (grid[i][j]) {
                    if (s == 0) dp[next][nmask] = (dp[next][nmask] + val) % MOD;
                    continue;
                }

                if (s == 0) {
                    if (i + 1 < n && j + 1 < m)
                        dp[next][nmask | (1 << (2 * j)) | (1 << (2 * (j + 1)))] = (dp[next][nmask | (1 << (2 * j)) | (1 << (2 * (j + 1)))] + val) % MOD;
                    if (i + 2 < n)
                        dp[next][nmask | (2 << (2 * j))] = (dp[next][nmask | (2 << (2 * j))] + val) % MOD;
                    if (j + 2 < m)
                        dp[next][nmask | (3 << (2 * (j + 1)))] = (dp[next][nmask | (3 << (2 * (j + 1)))] + val) % MOD;
                } else if (s == 1) {
                    dp[next][nmask] = (dp[next][nmask] + val) % MOD;
                    if (i + 1 < n)
                        dp[next][nmask | (1 << (2 * j))] = (dp[next][nmask | (1 << (2 * j))] + val) % MOD;
                } else if (s == 2) {
                    if (j + 1 < m)
                        dp[next][nmask | (1 << (2 * (j + 1)))] = (dp[next][nmask | (1 << (2 * (j + 1)))] + val) % MOD;
                } else if (s == 3) {
                    if (i + 1 < n)
                        dp[next][nmask | (1 << (2 * j))] = (dp[next][nmask | (1 << (2 * j))] + val) % MOD;
                }
            }
            cur = next;
        }
    }
    printf("%lld\n", dp[cur][0]);
}

int main() {
    freopen("input.txt", "r", stdin);
    int t;
    if (scanf("%d", &t) == 1) {
        while (t--) {
            solve();
        }
    }
    return 0;
}