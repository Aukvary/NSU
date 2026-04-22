#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long long i64;

i64 gcd(i64 a, i64 b) {
    while (b) {
        a %= b;
        i64 tmp = a;
        a = b;
        b = tmp;
    }
    return a;
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    i64* a = malloc(n * sizeof(i64));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    srand(time(NULL));

    i64 ans = 1;
    int needed = (n + 1) / 2;

    for (int iter = 0; iter < 40; iter++) {
        i64 val = a[rand() % n];
        i64* divs = malloc(2000 * sizeof(i64));
        int d_cnt = 0;

        for (i64 i = 1; i * i <= val; i++) {
            if (val % i == 0) {
                divs[d_cnt++] = i;
                if (i * i != val) {
                    divs[d_cnt++] = val / i;
                }
            }
        }

        for (int i = 0; i < d_cnt; i++) {
            i64 d = divs[i];
            if (d <= ans) continue;

            int count = 0;
            for (int j = 0; j < n; j++) {
                if (a[j] % d == 0) {
                    count++;
                }
            }

            if (count >= needed) {
                ans = d;
            }
        }
        free(divs);
    }

    printf("%lld\n", ans);

    free(a);
    return 0;
}