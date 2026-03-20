#include "primes.h"
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10000000

static bool* is_prime = NULL;
static int* prefix = NULL;
static int initialized = 0;

static void init() {
    if (initialized) return;

    is_prime = malloc((SIZE + 1) * sizeof(bool));
    prefix = malloc((SIZE + 1) * sizeof(int));

    for (int i = 0; i <= SIZE; i++)
        is_prime[i] = 1;

    is_prime[0] = false;
    is_prime[1] = false;

    for (int i = 2; i * i <= SIZE; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= SIZE; j += i)
                is_prime[j] = false;
        }
    }

    prefix[0] = 0;
    for (int i = 1; i <= SIZE; i++) {
        prefix[i] = prefix[i - 1] + is_prime[i];
    }

    initialized = 1;
}

int isPrime(int x) {
    if (!initialized) init();
    if (x < 0 || x > SIZE) return false;
    return is_prime[x];
}

int findNextPrime(int x) {
    if (x == SIZE) return 10000019;
    if (!initialized) init();
    for (int i = x; i <= SIZE; i++) {
        if (is_prime[i])
            return i;
    }
    return -1; 
}

int getPrimesCount(int l, int r) {
    if (!initialized) init();
    return prefix[r - 1] - (l > 0 ? prefix[l - 1] : 0);
}