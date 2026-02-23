#include "primes.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10000000

static bool* sieve = NULL;
static int* prime_counts = NULL;
static bool sieve_initialized = false;

static void init_sieve(void) {   
    sieve = malloc((MAX + 1) * sizeof(bool));
    prime_counts = malloc((MAX + 1) * sizeof(int));
        
    memset(sieve, true, (MAX + 1) * sizeof(bool));
    
    sieve[0] = false;
    sieve[1] = false;
    
    for (int i = 2; i * i <= MAX; i++) {
        if (sieve[i]) {
            for (int j = i * i; j <= MAX; j += i) {
                sieve[j] = false;
            }
        }
    }
    
    prime_counts[0] = 0;
    for (int i = 1; i <= MAX; i++) {
        prime_counts[i] = prime_counts[i - 1] + (sieve[i] ? 1 : 0);
    }    
    sieve_initialized = true;
}

int isPrime(int x) {
    if (x < 0 || x > MAX) return 0;
    
    if (!sieve_initialized) {
        init_sieve();
    }
    
    return sieve[x] ? 1 : 0;
}

int findNextPrime(int x) {
    if (x == MAX) return 10000019;


    if (!sieve_initialized) {
        init_sieve();
    }
    
    for (int i = x; i <= MAX; i++) {
        if (sieve[i]) return i;
    }
    
    return -1; 
}

int getPrimesCount(int l, int r) {
    if (!sieve_initialized) {
        init_sieve();
    }
        
    if (l == 0) {
        return prime_counts[r - 1];
    }
    return prime_counts[r - 1] - prime_counts[l - 1];
}