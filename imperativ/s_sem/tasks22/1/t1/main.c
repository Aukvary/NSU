#include "modular.h"
#include <assert.h>

static int ref_norm(int x)
{
    int r = x % MOD;
    if (r < 0) {
        r += MOD;
    }
    return r;
}

static int ref_mul(int a, int b)
{
    return (int)((1LL * a * b) % MOD);
}

static int ref_inv(int a)
{
    long long r0 = MOD, r1 = a;
    long long t0 = 0, t1 = 1;

    while (r1 != 0) {
        long long q = r0 / r1;

        long long nr = r0 - q * r1;
        r0 = r1;
        r1 = nr;

        long long nt = t0 - q * t1;
        t0 = t1;
        t1 = nt;
    }

    t0 %= MOD;
    if (t0 < 0) {
        t0 += MOD;
    }

    return (int)t0;
}

static int ref_div(int a, int b)
{
    return ref_mul(a, ref_inv(b));
}

static void test_small_mod(int p)
{
    MOD = p;

    int vals[] = {0, 1, p - 1, p, p + 1, -1, -p, -p - 1, 45, -45};
    int n = (int)(sizeof(vals) / sizeof(vals[0]));

    for (int i = 0; i < n; i++) {
        assert(pnorm(vals[i]) == ref_norm(vals[i]));
    }

    for (int a = 0; a < MOD; a++) {
        for (int b = 0; b < MOD; b++) {
            assert(padd(a, b) == ref_norm(a + b));
            assert(psub(a, b) == ref_norm(a - b));
            assert(pmul(a, b) == ref_mul(a, b));
            if (b != 0) {
                assert(pdiv(a, b) == ref_div(a, b));
            }
        }
    }
}

static void test_hard_div_cases(int p)
{
    MOD = p;

    assert(pnorm(p) == 0);
    assert(pnorm(-p) == 0);
    assert(padd(p - 1, 1) == 0);
    assert(psub(0, 1) == p - 1);
    assert(pmul(p - 1, p - 1) == 1);

    int found_big_big = 0;
    int found_big_small = 0;

    for (int b = 2; b < MOD && (found_big_big < 8 || found_big_small < 8); b++) {
        int inv = ref_inv(b);

        /* делитель большой, обратный тоже большой */
        if (b > 46340 && inv > 46340 && found_big_big < 8) {
            assert(pdiv(MOD - 2, b) == ref_div(MOD - 2, b));
            assert(pdiv(MOD - 123, b) == ref_div(MOD - 123, b));
            assert(pdiv(46341, b) == ref_div(46341, b));
            assert(pdiv(b, b) == 1);
            found_big_big++;
        }

        /* делитель большой, обратный маленький */
        if (b > 46340 && inv < 10 && found_big_small < 8) {
            assert(pdiv(MOD - 2, b) == ref_div(MOD - 2, b));
            assert(pdiv(46341, b) == ref_div(46341, b));
            assert(pdiv(7, b) == ref_div(7, b));
            found_big_small++;
        }
    }
}

int main(void)
{
    test_small_mod(2);
    test_small_mod(3);
    test_small_mod(5);
    test_small_mod(13);
    test_small_mod(17);

    MOD = 50021;
    assert(pmul(50020, 50020) == 1);

    test_hard_div_cases(50021);
    test_hard_div_cases(65537);
    return 0;
}