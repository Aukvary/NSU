#include <stdio.h>

int main() {
    int min = 0x7FFFFFFF;
    int min_i;
    int max = 0x80000000;
    int max_i;

    printf("%d\n", min);
    printf("%d\n", max);

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

    return 0;
}