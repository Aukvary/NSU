#include "modular.h"

int MOD = 2;

static int ppow(int a, int e)
{
    long long res = 1;
    long long base = a;

    while (e > 0) {
        if (e & 1) {
            res = (res * base) % MOD;
        }
        base = (base * base) % MOD;
        e >>= 1;
    }

    return (int)res;
}

int pnorm(int x)
{
    int r = x % MOD;
    if (r < 0) {
        r += MOD;
    }
    return r;
}

int padd(int a, int b)
{
    return (int)(((long long)a + b) % MOD);
}

int psub(int a, int b)
{
    int r = a - b;
    if (r < 0) {
        r += MOD;
    }
    return r;
}

int pmul(int a, int b)
{
    return (int)(((long long)a * b) % MOD);
}

int pdiv(int a, int b)
{
    return pmul(a, ppow(b, MOD - 2));
}