#include <stdio.h>
#include <stdlib.h>

typedef long long i64;

i64 mul_mod(i64 a, i64 b, i64 mod) {
    i64 res = 0;
    a %= mod;
    while (b) {
        if (b & 1) res = (res + a) % mod;
        a = (2 * a) % mod;
        b >>= 1;
    }
    return res;
}

i64 mod_inv(i64 a, i64 m) {
    i64 m0 = m;
    i64 t;
    i64 q;
    i64 x0 = 0;
    i64 x1 = 1;
    
    if (m == 1) return 0;
    
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    
    if (x1 < 0) x1 += m0;
    return x1;
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
        i64 inv = mod_inv(m_i % ms[i], ms[i]);
        i64 term = mul_mod(mul_mod(as[i], m_i, m), inv, m);
        x = (x + term) % m;
    }
    
    x = (x + m) % m;
    
    printf("%lld\n", x);
    
    free(ms);
    free(as);
    return 0;
}