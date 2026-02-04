#include <stdio.h>
#include <math.h>

#define LIMIT 1000000000000000LL

typedef long long i64;

void func(i64 p) {
    if (p % 4 != 1) {
        printf("no solutions\n");
        return;
    }
    
    i64 m0 = 0;
    i64 d0 = 1;
    i64 a0 = (i64)sqrt(p);
    
    i64 m = m0;
    i64 d = d0;
    i64 a = a0;
    
    i64 p1 = 0, q1 = 1;
    i64 p2 = 1, q2 = 0;
    
    while (1) {
        i64 p_curr = a * p2 + p1;
        i64 q_curr = a * q2 + q1;
        
        if (p_curr > LIMIT || q_curr > LIMIT) {
            printf("no solutions\n");
            return;
        }
        
        if (p_curr * p_curr - p * q_curr * q_curr == -1) {
            printf("%lld %lld\n", p_curr, q_curr);
            return;
        }
        
        p1 = p2;
        q1 = q2;
        p2 = p_curr;
        q2 = q_curr;
        
        m = d * a - m;
        d = (p - m * m) / d;
        a = (a0 + m) / d;
    }
}

int main(void) {
    freopen("input.txt", "r", stdin);
    
    int t;
    i64 p;
    
    scanf("%d", &t);
    
    while (t--) {
        scanf("%lld", &p);
        func(p);
    }
    
    return 0;
}