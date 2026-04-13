#include "modular.h"
#include <assert.h>
#include <limits.h>

static int ref_normalize(int val) {
    int rem = val % MOD;
    if (rem < 0) {
        rem += MOD;
    }
    return rem;
}

static int ref_multiply(int x, int y) {
    return (int)((1LL * x * y) % MOD);
}

static int ref_inverse(int val) {
    long long r0 = MOD, r1 = val;
    long long s0 = 0, s1 = 1;

    while (r1 != 0) {
        long long quotient = r0 / r1;
        long long new_r = r0 - quotient * r1;
        r0 = r1;
        r1 = new_r;
        long long new_s = s0 - quotient * s1;
        s0 = s1;
        s1 = new_s;
    }

    s0 %= MOD;
    if (s0 < 0) {
        s0 += MOD;
    }
    return (int)s0;
}

static int ref_divide(int dividend, int divisor) {
    return ref_multiply(dividend, ref_inverse(divisor));
}

static void test_mod_small(int prime) {
    MOD = prime;

    int samples[] = {0, 1, prime - 1, prime, prime + 1, -1, -prime, -prime - 1, 45, -45, INT_MAX, INT_MIN};
    int sample_count = sizeof(samples) / sizeof(samples[0]);

    for (int idx = 0; idx < sample_count; idx++) {
        assert(pnorm(samples[idx]) == ref_normalize(samples[idx]));
    }

    int test_values[] = {0, 1, 2, prime/2, prime-2, prime-1};
    int tv_count = sizeof(test_values) / sizeof(test_values[0]);

    for (int i = 0; i < tv_count; i++) {
        for (int j = 0; j < tv_count; j++) {
            int a = test_values[i];
            int b = test_values[j];
            if (a < 0 || a >= prime) continue;
            if (b < 0 || b >= prime) continue;
            assert(padd(a, b) == ref_normalize(a + b));
            assert(psub(a, b) == ref_normalize(a - b));
            assert(pmul(a, b) == ref_multiply(a, b));
            if (b != 0) {
                assert(pdiv(a, b) == ref_divide(a, b));
            }
        }
    }
}

static void test_edge_cases(int prime) {
    MOD = prime;

    assert(pnorm(prime) == 0);
    assert(pnorm(-prime) == 0);
    assert(padd(prime - 1, 1) == 0);
    assert(psub(0, 1) == prime - 1);
    assert(pmul(prime - 1, prime - 1) == 1);

    assert(pdiv(0, 1) == 0);
    assert(pdiv(1, 1) == 1);
    assert(pdiv(prime - 1, 1) == prime - 1);
    assert(pdiv(1, prime - 1) == prime - 1);
    assert(pdiv(prime - 1, prime - 1) == 1);
}

static void test_mod_change() {
    MOD = 7;
    assert(pnorm(10) == 3);
    assert(padd(5, 6) == 4);
    assert(psub(5, 6) == 6);
    assert(pmul(3, 5) == 1);
    assert(pdiv(3, 5) == 2);

    MOD = 13;
    assert(pnorm(10) == 10);
    assert(padd(5, 6) == 11);
    assert(psub(5, 6) == 12);
    assert(pmul(3, 5) == 2);
    assert(pdiv(3, 5) == 8);

    MOD = 7;
    assert(pnorm(10) == 3);
    assert(padd(5, 6) == 4);
}

static void test_large_prime() {
    MOD = 1000000007;
    assert(pnorm(2000000000) == 2000000000 % MOD);
    assert(pmul(1000000006, 1000000006) == 1);
    assert(pdiv(1, 2) == 500000004);
    assert(pmul(2, 500000004) == 1);
    assert(pdiv(1000000006, 1000000006) == 1);
}

int main(void) {
    test_mod_small(2);
    test_mod_small(3);
    test_mod_small(5);
    test_mod_small(13);
    test_mod_small(17);

    MOD = 50021;
    assert(pmul(50020, 50020) == 1);

    test_edge_cases(50021);
    test_edge_cases(65537);
    test_mod_change();
    test_large_prime();

    return 0;
}