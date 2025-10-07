#include <stdio.h>

double s(double x) {
    double result = x;        
    double term = x;          
    int n = 1;                
    
    while (term > 1e-20 || term < -1e-20) {
        term = -term * x * x / ((2 * n) * (2 * n + 1));
        result += term;
        n++;
        
        if (n > 1000) 
            break;
    }
    
    return result;
}

int main() {
    int n;

    FILE* in = fopen("input.txt", "r");

    fscanf(in, "%d", &n);

    for (int i = 0; i < n; i++) {
        double a;
        fscanf(in, "%lf", &a);
        printf("%0.15lf\n", s(a));
    }

    return 0;
}