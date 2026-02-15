#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long i64;
typedef unsigned int u32;
typedef unsigned long long u64;

#define MOD 1000000000ULL
#define SIZE 500

typedef struct {
    u32 d[SIZE];  
    int len;
} LongNum;

void long_num_trim(LongNum *a) {
    while (a->len > 1 && a->d[a->len - 1] == 0) a->len--;
}

void long_num_new(LongNum *a, i64 x) {
    a->len = 0;
    if (x == 0) {
        a->d[0] = 0;
        a->len = 1;
        return;
    }
    while (x > 0) {
        a->d[a->len++] = (u32)(x % (i64)MOD);
        x /= (i64)MOD;
    }
}

void long_num_copy(LongNum *dst, const LongNum *src) {
    dst->len = src->len;
    for (int i = 0; i < src->len; i++) dst->d[i] = src->d[i];
}

void long_num_add(LongNum *a, const LongNum *b) {
    u64 carry = 0;
    int n = (a->len > b->len ? a->len : b->len);
    for (int i = 0; i < n || carry; i++) {
        if (i == a->len) a->d[a->len++] = 0;
        u64 cur = carry + a->d[i] + (u64)(i < b->len ? b->d[i] : 0);
        a->d[i] = (u32)(cur % MOD);
        carry = cur / MOD;
    }
    long_num_trim(a);
}

void long_num_mul(LongNum *a, i64 m) {
    if (m == 0) { 
        long_num_new(a, 0); 
        return; 
    }
    u64 carry = 0;
    for (int i = 0; i < a->len; i++) {
        u64 cur = (u64)a->d[i] * (u64)m + carry;
        a->d[i] = (u32)(cur % MOD);
        carry = cur / MOD;
    }
    while (carry) {
        a->d[a->len++] = (u32)(carry % MOD);
        carry /= MOD;
    }
    long_num_trim(a);
}

i64 long_num_mod(const LongNum *a, i64 m) {
    u64 r = 0;
    for (int i = a->len - 1; i >= 0; i--) {
        r = (r * MOD + a->d[i]) % (u64)m;
    }
    return (i64)r;
}

void long_num_print(const LongNum *a) {
    printf("%u", a->d[a->len - 1]);
    for (int i = a->len - 2; i >= 0; i--) {
        printf("%u", a->d[i]);
    }
    printf("\n");
}

i64 long_num_egcd(i64 a, i64 b, i64 *x, i64 *y) {
    if (b == 0) { 
        *x = 1; 
        *y = 0; 
        return a; 
    }
    i64 x1, y1;
    i64 g = long_num_egcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - y1 * (a / b);
    return g;
}

i64 long_num_modinv(i64 a, i64 m) {
    i64 x, y;
    long_num_egcd(a, m, &x, &y);
    x %= m;
    if (x < 0) x += m;
    return x;
}

int main() {
    int k;
    scanf("%d", &k);

    i64 m[2005];
    i64 a[2005];
    for (int i = 0; i < k; i++) scanf("%lld", &m[i]);
    for (int i = 0; i < k; i++) scanf("%lld", &a[i]);

    LongNum cur;
    LongNum mod;
    LongNum tmp;
    long_num_new(&cur, a[0]);
    long_num_new(&mod, m[0]);

    for (int i = 1; i < k; i++) {
        i64 m_i = m[i];
        i64 a_i = a[i];

        i64 cur_mod = long_num_mod(&cur, m_i);
        i64 rhs = (a_i - cur_mod) % m_i;
        if (rhs < 0) rhs += m_i;

        i64 mod_mod = long_num_mod(&mod, m_i);
        i64 inv = long_num_modinv(mod_mod, m_i);
        i64 t = (rhs * inv) % m_i;

        long_num_copy(&tmp, &mod);
        long_num_mul(&tmp, t);
        long_num_add(&cur, &tmp);

        long_num_mul(&mod, m_i);
    }

    long_num_print(&cur);
    return 0;
}