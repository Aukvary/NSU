#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double Function(double x);

double func(double x) {
    double h = 1e-7; 
    
    if (x < h) {
        return (Function(x + h) - Function(x)) / h;
    } else if (x > 1.0 - h) {
        return (Function(x) - Function(x - h)) / h;
    } else {
        return (Function(x + h) - Function(x - h)) / (2.0 * h);
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        double x;
        scanf("%lf", &x);
        double d = func(x);
        printf("%.15f\n", d);
    }

    return 0;
}