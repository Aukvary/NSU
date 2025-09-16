#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int min = 0;
    int zero = 0;
    int max = 0;

    for (int i = 0; i < n; i++) {
        int a;

        scanf("%d", &a);

        if (a < 0) {
            min += 1;
        } else if (a == 0) {
            zero += 1;
        } else {
            max += 1;
        }
    }

    double count = (double)n;

    printf("%.5f, %.5f, %.5f", min / count, zero / count, max/ count);
    
    return 0;
}