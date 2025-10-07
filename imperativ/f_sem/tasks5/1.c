#include <stdio.h>

double e(double x) {
    if (x < 0) {
        return 1.0 / e(-x);
    }
    
    double result = 1.0;
    double term = 1.0;
    int n = 1;                
    
    while (term > 1e-15 || term < -1e-15) {
        term = term * x / n;  
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
        printf("%0.15g\n", e(a));
    }

    return 0;
}