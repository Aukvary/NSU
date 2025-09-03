#include <stdio.h>
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
    } else if (y <= 0) {
        printf("%d", -2);
    } else if (z <= 0) {
        printf("%d", -3);
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
            break;
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
    int min;
    int min_i;

    int max;
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
    //
}

void t1_task8() {
    //
}

void t1_task9() {
    int n;
    scanf("%d", &n);

    int count = 0;

    for (int i = 0; i * i * i <= n; i++) {
        for (int j = i; i * i * j <= n; i++) {
            for (int k = j; i * j * k <= n; n++) {
                count++;
            }
        }
    }

    printf("%d\n", count);
}