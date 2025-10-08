#include <stdio.h>
#include <math.h>

double cos_func(double a, double b, double c) {
    return (a*a + b*b - c*c) / (2 * a * b);
}

int main() {
    double x1, y1;
    double x2, y2;
    double x3, y3;

    int n;
    FILE* in = fopen("input.txt", "r");
    
    for (int i = 0; i < n; i++) {
        fscanf(in, "%lf %lf %lf %lf %lf %lf", x1, y1, x2, y2, x3, y3);
    }

    return 0;
}