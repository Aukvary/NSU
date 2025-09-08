#include <stdio.h>

int main (void) {
    int n;

    scanf("%d", &n);

    if (n <= 1) {
        printf("NO\n");
        return 0;
    }

    float sqrt_n = (int)sqrtf((float)n) + 1;

    for (int i = 2; i < sqrt_n; i++) {
        if (n % i == 0) {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");

    return 0;
}