#include <stdio.h>
#define MOD 1000000007

typedef long long i64;

i64 mod(i64 a, i64 b) {
    i64 res = 1;
    a %= MOD;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

i64 C(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    
    i64 num = 1;
    i64 d = 1;
    for (int i = 1; i <= k; i++) {
        num = num * (n - k + i) % MOD;
        d = d * i % MOD;
    }
    return num * mod(d, MOD - 2) % MOD;
}

int main(void) {
    freopen("input.txt", "r", stdin);
    
    int t;
    int n;
    int k;
    scanf("%d", &t);
    
    while (t--) {
        scanf("%d %d", &n, &k);
        printf("%lld\n", C(n, k));
    }
    
    return 0;
}