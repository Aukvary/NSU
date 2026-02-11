#include <math.h>
#include <stdio.h>

#define EPS 1e-12
#define ITER_EPS 1e-10
#define MAX_ITER 100000
#define SIZE 200

int n;

double a[SIZE][SIZE];
double b[SIZE];
double x[SIZE];

int seidel() {
    for (int i = 0; i < n; i++) {
        x[i] = 0.0;
    }
    
    for (int iter = 0; iter < MAX_ITER; iter++) {
        double max_diff = 0.0;
        
        for (int i = 0; i < n; i++) {
            double old_x = x[i];
            double sum = b[i];
            
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum -= a[i][j] * x[j];
                }
            }
            
            x[i] = sum / a[i][i];
            double diff = fabs(x[i] - old_x);
            if (diff > max_diff) max_diff = diff;
        }
        
        if (max_diff < ITER_EPS) {
            return 1; 
        }
    }
    
    return 0; 
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &a[i][j]);
        }
        scanf("%lf", &b[i]);
    }
    
    
    
    return 0;
}