#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void t1_task1() {
    int n;
    scanf("%d", &n);

    int res = 0;
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);

        if (a % 2 == 1)
            res += a;
    }

    printf("%d\n", res);
}

void t1_task2() {
    int x, y, z;

    scanf("%d %d %d", &x, &y, &z);

    if (x <= 0) {
        printf("%d", -1);
        return;
    } else if (y <= 0) {
        printf("%d", -2);
        return;
    } else if (z <= 0) {
        printf("%d", -3);
        return;
    }

    printf("%d\n", (x * y + x * z + y * z) * 2);
}

void t1_task3() {
    int n;
    scanf("%d", &n);

    int count = 0;

    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);

        count += 2;

        if (a % 10 == 9) {
            count -= 1;
        } else if (a % 10 == 0) {
            a /= 10;
            count += 1;
            while (a > 0) {
                if (a % 10 == 0) count += 1;
                a /= 10;
            }
        }
    }

    printf("%d\n", count);
}

void t1_task4() {
    int n;

    scanf("%d", &n);

    if (n <= 1) {
        printf("NO\n");
        return;
    }

    float sqrt_n = (int)sqrtf((float)n) + 1;

    for (int i = 2; i < sqrt_n; i++) {
        if (n % i == 0) {
            printf("NO\n");
            return;
        }
    }

    printf("YES\n");
}

void t1_task5() {
    float a, b;

    scanf("%f %f", &a, &b);

    printf("%d ", (int)floor(a / b));
    printf("%d ", (int)ceil(a / b));
    printf("%d ", (int)round(a / b));
    printf("%d", (int)floor(a / b)); //------//
}

void t1_task6() {
    int min = INT_MAX;
    int min_i;

    int max = INT_MIN;
    int max_i;

    int n;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);

        if (a < min) {
            min = a;
            min_i = i;
        } else if (a > max) {
            max = a;
            max_i = i;
        }
    }

    printf("%d %d %d %d\n", min, min_i + 1, max, max_i + 1);
}

void t1_task7() {
    int n;
    int m/*номер*/, p/*подъезд*/, k/*этаж*/, l/*кол-во этажей*/;

    scanf("%d", &n);
    scanf("%d %d %d %d", &m, &p, &k, &l);

    float g = l * (p - 1) + k - 1;
    int c;
    
    for (int i = 1; i < INT_MAX; i++) {
        float j = (m - i) / g;
        
        if (j == (int)j) {
            c = j;
            break;            
        }
    }

    int i;
    for (i = 1; i * l * c < n; i++);

    int j;
    for (j = 1; (i-1) * l * c + j * c <= n; j++);

    printf("%d %d", i, j - 1);
}

void t1_task8() {
    int h, m, s, k;

    scanf("%d %d %d %d", &h, &m, &s, &k);

    s += k;
    m += s / 60;
    s %= 60;
    h += m / 60;
    m %= 60;
    h %= 24;

    printf("%d %d %d", h, m, s);
}

typedef long long i64;

void t1_task9() {
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