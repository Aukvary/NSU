#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int find_b(int a, int m) {
    int start_m = m;
    int y = 0;
    int x = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        int q = a / m;
        int tmp = m;

        m = a % m;
        a = tmp;
        tmp = y;

        y = x - q * y;
        x = tmp;
    }

    if (x < 0)
        x += start_m;

    return x;
}

long long C(int n, int k, int m) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;

    long long res = 1;

    for (int i = 1; i <= k; i++) {
        res = (res * (n - k + i)) % m;

        int inv_i = 1;

        if (gcd(i, m) == 1) inv_i = find_b(i, m);

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
