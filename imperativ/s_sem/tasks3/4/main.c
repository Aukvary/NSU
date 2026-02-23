#include <stdio.h>

typedef struct Factors {
    int k;
    int primes[32];
    int powers[32];
} Factors;

void Factorize(int X, Factors *res);

int main() {
    freopen("input.txt", "r", stdin);

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);

        Factors f;
        Factorize(x, &f);

        printf("%d = ", x);
        if (f.k == 0) {
            printf("1\n");
        } else {
            for (int j = 0; j < f.k; j++) {
                printf("%d^%d", f.primes[j], f.powers[j]);
                if (j < f.k - 1) {
                    printf(" * ");
                }
            }
            printf("\n");
        }
    }

    return 0;
}