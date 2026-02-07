#include <stdio.h>
#include <stdlib.h>

typedef long long i64;

i64 mul_mod(i64 a, i64 b, i64 mod) {
    i64 res = 0;
    a %= mod;
    while (b) {
        if (b & 1) res = (res + a) % mod;
        a = (a << 1) % mod;
        b >>= 1;
    }
    return res;
}

i64 find_b(i64 a, i64 m) {
    i64 start_m = m;
    i64 y = 0;
    i64 x = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        i64 q = a / m;
        i64 tmp = m;

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

int main(void) {
    freopen("input.txt", "r", stdin);

    int k;
    scanf("%d", &k);

    i64* ms = malloc(k * sizeof(i64));
    i64* as = malloc(k * sizeof(i64));

    for (int i = 0; i < k; i++) {
        scanf("%lld", &ms[i]);
    }

    for (int i = 0; i < k; i++) {
        scanf("%lld", &as[i]);
    }

    i64 m = 1;
    for (int i = 0; i < k; i++) {
        m *= ms[i];
    }

    i64 x = 0;

    for (int i = 0; i < k; i++) {
        i64 m_i = m / ms[i];
        i64 inv = find_b(m_i % ms[i], ms[i]);
        i64 term = mul_mod(mul_mod(as[i], m_i, m), inv, m);
        x = (x + term) % m;
    }

    x = (x + m) % m;

    printf("%lld\n", x);

    free(ms);
    free(as);
    return 0;
}
