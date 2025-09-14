#include <stdio.h>

int main() {
    int min = 10001;
    int min_i;
    int max = -10001;
    int max_i;

    int n;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);

        if (a < min) {
            min = a;
            min_i = i;
        } 
        if (a > max) {
            max = a;
            max_i = i;
        }
    }

    printf("%d %d %d %d\n", min, min_i + 1, max, max_i + 1);

    return 0;
}
