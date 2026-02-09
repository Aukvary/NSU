#include <stdio.h>

typedef unsigned long long u64;

u64 C(u64 n, u64 k, u64 m) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    if (k == 1) return n % m;
    if (k > n - k) k = n - k;
    
    u64 a = C(n-1, k-1, m);
    u64 b = C(n-1, k, m);
    
    return (a + b) % m;
}

int main(void) {
    freopen("input.txt", "r", stdin);

    int m;
    int t;
    int n;
    int k;

    scanf("%d %d", &m, &t);

    while (t--) {
        scanf("%d %d", &n, &k);

        printf("%lld\n", C(n, k, m));
    }

    return 0;
}
