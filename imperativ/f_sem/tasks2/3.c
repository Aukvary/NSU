#include <stdio.h>

int main() {
    double n;
    scanf("%lf", &n);

    double min = 0;
    double zero = 0;
    double max = 0;

    for (int i = 0; i < n; i++) {
        double a;

        scanf("%lf", &a);

        if (a < 0) {
            min += 1;
        } else if (a == 0) {
            zero += 1;
        } else {
            max += 1;
        }
    }

    printf("%.5lf, %.5lf, %.5lf", min / n, zero / n, max/ n);
    
    return 0;
}