#include "modular.h"
#include <assert.h>

int main() {
    MOD = 13;
    
    assert(pnorm(0) == 0);
    assert(pnorm(5) == 5);
    assert(pnorm(12) == 12);
    assert(pnorm(13) == 0);
    assert(pnorm(14) == 1);
    assert(pnorm(25) == 12);
    assert(pnorm(26) == 0);
    assert(pnorm(-1) == 12);
    assert(pnorm(-2) == 11);
    assert(pnorm(-13) == 0);
    assert(pnorm(-14) == 12);
    assert(pnorm(-25) == 1);
    assert(pnorm(-26) == 0);
    
    assert(padd(0, 0) == 0);
    assert(padd(5, 7) == 12);
    assert(padd(5, 8) == 0);
    assert(padd(10, 5) == 2);
    assert(padd(12, 1) == 0);
    assert(padd(12, 2) == 1);
    
    assert(psub(5, 3) == 2);
    assert(psub(3, 5) == 11);
    assert(psub(0, 1) == 12);
    assert(psub(1, 0) == 1);
    assert(psub(12, 12) == 0);
    assert(psub(0, 0) == 0);
    
    assert(pmul(0, 5) == 0);
    assert(pmul(5, 0) == 0);
    assert(pmul(1, 5) == 5);
    assert(pmul(2, 6) == 12);
    assert(pmul(2, 7) == 1);
    assert(pmul(3, 4) == 12);
    assert(pmul(3, 5) == 2);
    assert(pmul(12, 12) == 1);
    
    assert(pdiv(1, 1) == 1);
    assert(pdiv(1, 2) == 7);
    assert(pmul(2, pdiv(1, 2)) == 1);
    assert(pdiv(5, 2) == 9);
    assert(pmul(2, 9) == 5);
    assert(pdiv(7, 3) == 11);
    assert(pmul(3, 11) == 7);
    assert(pdiv(12, 5) == 5);
    assert(pmul(5, 5) == 12);
    assert(pdiv(0, 7) == 0);
    
    int x = pmul(padd(7, psub(2, 3)), 5);
    assert(x == 4);
    int y = pdiv(7, x);
    assert(pmul(x, y) == 7);
    
    MOD = 2;
    assert(pnorm(0) == 0);
    assert(pnorm(1) == 1);
    assert(pnorm(2) == 0);
    assert(pnorm(3) == 1);
    assert(pnorm(-1) == 1);
    assert(pnorm(-2) == 0);
    assert(padd(0, 0) == 0);
    assert(padd(0, 1) == 1);
    assert(padd(1, 1) == 0);
    assert(psub(0, 1) == 1);
    assert(psub(1, 0) == 1);
    assert(psub(1, 1) == 0);
    assert(pmul(0, 0) == 0);
    assert(pmul(0, 1) == 0);
    assert(pmul(1, 1) == 1);
    assert(pdiv(1, 1) == 1);
    
    MOD = 7;
    for (int i = 1; i < 7; i++) {
        for (int j = 1; j < 7; j++) {
            assert(pmul(pdiv(i, j), j) == i);
        }
    }
    
    MOD = 1000000007;
    assert(pnorm(1000000007) == 0);
    assert(pnorm(-1000000007) == 0);
    assert(padd(1000000006, 1) == 0);
    assert(padd(1000000006, 2) == 1);
    assert(psub(0, 1) == 1000000006);
    assert(pmul(1000000006, 2) == 1000000005);
    assert(pmul(1000000006, 1000000006) == 1);
    assert(pdiv(1, 1000000006) == 1000000006);
    
    MOD = 3;
    assert(pnorm(0) == 0);
    assert(pnorm(1) == 1);
    assert(pnorm(2) == 2);
    assert(pnorm(3) == 0);
    assert(padd(1, 2) == 0);
    assert(psub(1, 2) == 2);
    assert(pmul(2, 2) == 1);
    assert(pdiv(2, 2) == 1);
    
    MOD = 5;
    assert(pnorm(0) == 0);
    assert(pnorm(1) == 1);
    assert(pnorm(4) == 4);
    assert(pnorm(5) == 0);
    assert(padd(3, 4) == 2);
    assert(psub(1, 4) == 2);
    assert(pmul(2, 3) == 1);
    assert(pdiv(2, 3) == 4);
    assert(pmul(3, 4) == 2);
    
    MOD = 999983;
    assert(pmul(999982, 999982) == 1);
    assert(pdiv(1, 999982) == 999982);
    
    return 0;
}