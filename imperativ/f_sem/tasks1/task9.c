#include <stdio.h>
#include <math.h>

typedef long long i64;
int main(void) {
    i64 n;
    scanf("%lld", &n);
    
    i64 count = 0;
    i64 max_a = cbrt(n);
    
    for (i64 a = 1; a <= max_a; a++) {
        i64 m = n / a;
        i64 b_max = sqrt(m);
        
        for (i64 b = a; b <= b_max; b++) {
            i64 max_c = m / b;
            if (max_c >= b) {
                count += (max_c - b + 1);
            }
        }
    }
    
    printf("%lld\n", count);
}