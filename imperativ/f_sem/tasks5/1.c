#include <stdio.h>

int fac(int n) {
    if (n == 0) return 1;
    int res = 1;

    for (int i = 2; i <= n; i++) {
        res *= i;
    }

    return res;
}

double p(double x, int y) {
    double n = 1.0;

    for (int i = 0; i < y; i++) {
        n *= x;
    }

    return n;
}

#define ABS(x) (x < 0 ? -x : x)

double e(double x) {
    double res = 0;

    for (double i = 0; i <= ABS(x); i++) {
        res += p(x, i) / (double)fac((int)i);
    }

    return res;
}

int main() {
    int n;

    FILE* in = fopen("input.txt", "r");

    fscanf(in, "%d", &n);

    for (int i = 0; i < n; i++) {
        double a;
        fscanf(in, "%lf", &a);
        printf("%0.15g\n", e(a));
    }

    return 0;
}