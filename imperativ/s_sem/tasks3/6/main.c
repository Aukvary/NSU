#include "primes.h"
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

static bool* is_prime = NULL;
static int* prefix = NULL;
static int initialized = 0;

static void init() {
    if (initialized) return;

    is_prime = malloc((10000000 + 1) * sizeof(bool));
    prefix = malloc((10000000 + 1) * sizeof(int));

    for (int i = 0; i <= 10000000; i++)
        is_prime[i] = 1;

    is_prime[0] = false;
    is_prime[1] = false;

    for (int i = 2; i * i <= 10000000; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= 10000000; j += i)
                is_prime[j] = false;
        }
    }

    prefix[0] = 0;
    for (int i = 1; i <= 10000000; i++) {
        prefix[i] = prefix[i - 1] + is_prime[i];
    }

    initialized = 1;
}

static int test_isPrime(int x) {
    if (!initialized) init();
    if (x < 0 || x > 10000000) return false;
    return is_prime[x];
}

static int test_findNextPrime(int x) {
    if (x == 10000000) return 10000019;
    if (!initialized) init();
    if (x < 2) x = 2;
    for (int i = x; i <= 10000000; i++) {
        if (is_prime[i])
            return i;
    }
    return -1; 
}

static int test_getPrimesCount(int l, int r) {
    if (!initialized) init();
    if (l < 0) l = 0;
    if (r > 10000000 + 1) r = 10000000 + 1;
    if (l >= r) return 0;

    return prefix[r - 1] - (l > 0 ? prefix[l - 1] : 0);
}

int main() {
    const int N = 10000000;  

    for (int x = 0; x <= N; x++) {
        assert(isPrime(x) == test_isPrime(x));
    }

    for (int x = 0; x <= N; x++) {
        assert(findNextPrime(x) == test_findNextPrime(x));
    }

    for (int l = 0; l <= N; l++) {
        for (int r = l; r <= N; r++) {
            assert(getPrimesCount(l, r) == test_getPrimesCount(l, r));
        }
    }

    return 0;
}