#include "modular.h"

int MOD;

int pnorm(int a) {
    int r = a % MOD;
    if (r < 0) r += MOD;
    return r;
}

int padd(int a, int b) {
    int r = a + b;
    if (r >= MOD) r -= MOD;
    return r;
}

int psub(int a, int b) {
    int r = a - b;
    if (r < 0) r += MOD;
    return r;
}

int pmul(int a, int b) {
    return (int)((long long)a * b % MOD);
}

static int mod_pow(int a, int e) {
    long long result = 1;
    long long base = a;
    while (e > 0) {
        if (e & 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        e >>= 1;
    }
    return (int)result;
}

static int mod_inv(int a) {
    return mod_pow(a, MOD - 2);
}

int pdiv(int a, int b) {
    return pmul(a, mod_inv(b));
}