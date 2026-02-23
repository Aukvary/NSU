#include "primes.h"
#include <assert.h>

int main() {
    assert(isPrime(0) == 0);
    assert(isPrime(1) == 0);
    assert(isPrime(2) == 1);
    
    assert(isPrime(3) == 1);
    assert(isPrime(4) == 0);
    assert(isPrime(5) == 1);
    assert(isPrime(9) == 0);
    assert(isPrime(11) == 1);
    assert(isPrime(15) == 0);
    
    assert(isPrime(49) == 0);
    assert(isPrime(121) == 0);
    
    assert(isPrime(97) == 1);
    assert(isPrime(101) == 1);
    assert(isPrime(997) == 1);
    
    assert(isPrime(999983) == 1);
    assert(isPrime(9999991) == 1);
    assert(isPrime(10000000) == 0);
    
    assert(findNextPrime(0) == 2);
    assert(findNextPrime(1) == 2);
    assert(findNextPrime(2) == 2);
    assert(findNextPrime(3) == 3);
    assert(findNextPrime(4) == 5);
    assert(findNextPrime(8) == 11);
    assert(findNextPrime(9) == 11);
    assert(findNextPrime(10) == 11);
    assert(findNextPrime(11) == 11);
    assert(findNextPrime(12) == 13);
    assert(findNextPrime(14) == 17);
    assert(findNextPrime(20) == 23);
    assert(findNextPrime(30) == 31);
    assert(findNextPrime(32) == 37);
    
    assert(findNextPrime(97) == 97);
    assert(findNextPrime(98) == 101);
    assert(findNextPrime(100) == 101);
    
    assert(getPrimesCount(1, 1) == 0);
    assert(getPrimesCount(5, 5) == 0);
    assert(getPrimesCount(10, 10) == 0);
    
    assert(getPrimesCount(1, 2) == 0);
    assert(getPrimesCount(1, 3) == 1);
    assert(getPrimesCount(2, 3) == 1);
    assert(getPrimesCount(1, 5) == 2);
    assert(getPrimesCount(2, 5) == 2);
    assert(getPrimesCount(3, 6) == 2);
    
    assert(getPrimesCount(1, 10) == 4);
    assert(getPrimesCount(1, 20) == 8);
    assert(getPrimesCount(1, 30) == 10);
    assert(getPrimesCount(1, 100) == 25);
    
    assert(getPrimesCount(10, 20) == 4);
    assert(getPrimesCount(20, 30) == 2);
    assert(getPrimesCount(90, 100) == 1);
    
    assert(getPrimesCount(1, 1000) == 168);
    assert(getPrimesCount(1, 10000) == 1229);
    
    int prime_count_100 = getPrimesCount(1, 100);
    int found = 0;
    for (int i = 2; i < 100; i++) {
        if (isPrime(i)) found++;
    }
    assert(found == prime_count_100);
    
    for (int i = 2; i <= 100; i++) {
        int next = findNextPrime(i);
        if (isPrime(i)) {
            assert(next == i);
        } else {
            assert(next > i);
            assert(isPrime(next) == 1);
        }
    }
    
    assert(findNextPrime(999990) > 999990);
    assert(isPrime(findNextPrime(999990)) == 1);
    
    return 0;
}