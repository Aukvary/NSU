#include <stdio.h>

long long C(int n, int k, int m) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    
    long long res = 1;
    
    for (int i = 1; i <= k; i++) {
        res = (res * (n - k + i)) % m;
        
        int inv_i = 1;

        for (int j = 1; j < m; j++) {
            if ((i * j) % m == 1) {
                inv_i = j;
                break;
            }
        }
        
        res = (res * inv_i) % m;
    }
    
    return res;
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