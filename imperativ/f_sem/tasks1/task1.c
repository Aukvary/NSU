#include <stdio.h>

int main(void) {
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

    return 0;
}