#include "modular.h"

int MOD;

static int inv_cache[1000000]; 
static int last_MOD = 0;

static int mod_inv(int a) {
    if (MOD <= 1000000 && last_MOD == MOD && inv_cache[a] != 0) {
        return inv_cache[a];
    }
    
    int t = 0, newt = 1;
    int r = MOD, newr = a;
    
    while (newr != 0) {
        int q = r / newr;
        int tmp = newt;
        newt = t - q * newt;
        t = tmp;
        
        tmp = newr;
        newr = r - q * newr;
        r = tmp;
    }
    
    if (t < 0) t += MOD;
    
    if (MOD <= 1000000) {
        last_MOD = MOD;
        inv_cache[a] = t;
    }
    
    return t;
}

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

int pdiv(int a, int b) {
    return pmul(a, mod_inv(b));
}