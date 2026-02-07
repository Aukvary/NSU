#include <stdio.h>
#include <math.h>

#define LIMIT 1000000000000000LL

typedef long long i64;

void func(i64 p) {
    if (p % 4 != 1) {
        printf("no solutions\n");
        return;
    }

    i64 start_m = 0;
    i64 start_d = 1;
    i64 start_a = (i64)sqrt(p);

    i64 m = start_m;
    i64 d = start_d;
    i64 a = start_a;

    i64 p1 = 0;
    i64 q1 = 1;
    i64 p2 = 1;
    i64 q2 = 0;

    while (1) {
        i64 cur_p = a * p2 + p1;
        i64 cur_q = a * q2 + q1;

        if (cur_p > LIMIT || cur_q > LIMIT) {
            printf("no solutions\n");
            return;
        }

        if (cur_p * cur_p - p * cur_q * cur_q == -1) {
            printf("%lld %lld\n", cur_p, cur_q);
            return;
        }

        p1 = p2;
        q1 = q2;
        p2 = cur_p;
        q2 = cur_q;

        m = d * a - m;
        d = (p - m * m) / d;
        a = (start_a + m) / d;
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
