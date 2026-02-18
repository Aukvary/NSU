#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 200
#define ZERO 1e-10
#define MAX_ITER 10000

int n;
double a[SIZE][SIZE];
double b[SIZE];
double x[SIZE];
double a_copy[SIZE][SIZE];
double b_copy[SIZE];

void gauss_slau() {
    double matrix[SIZE][SIZE + 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = a[i][j];
        }
        matrix[i][n] = b[i];
    }
    
    for (int i = 0; i < n; i++) {
        int max_row = i;
        double max_val = fabs(matrix[i][i]);
        for (int k = i + 1; k < n; k++) {
            if (fabs(matrix[k][i]) > max_val) {
                max_val = fabs(matrix[k][i]);
                max_row = k;
            }
        }
        
        if (max_row != i) {
            for (int j = i; j <= n; j++) {
                double temp = matrix[i][j];
                matrix[i][j] = matrix[max_row][j];
                matrix[max_row][j] = temp;
            }
        }
        
        if (fabs(matrix[i][i]) < ZERO) {
            return;
        }
        
        double divisor = matrix[i][i];
        for (int j = i; j <= n; j++) {
            matrix[i][j] /= divisor;
        }
        
        for (int k = i + 1; k < n; k++) {
            double factor = matrix[k][i];
            for (int j = i; j <= n; j++) {
                matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }
    
    for (int i = n - 1; i >= 0; i--) {
        x[i] = matrix[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= matrix[i][j] * x[j];
        }
    }
}

void iter_slau() {
    double x_old[SIZE] = {0.0};
    double x_new[SIZE];
    
    for (int iter = 0; iter < MAX_ITER; iter++) {
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += a_copy[i][j] * x_old[j];
                }
            }
            x_new[i] = (b_copy[i] - sum) / a_copy[i][i];
        }
        
        double max_diff = 0.0;
        for (int i = 0; i < n; i++) {
            double diff = fabs(x_new[i] - x_old[i]);
            if (diff > max_diff) {
                max_diff = diff;
            }
        }
        
        for (int i = 0; i < n; i++) {
            x_old[i] = x_new[i];
        }
        
        if (max_diff < 1e-6) {
            break;
        }
    }
    
    for (int i = 0; i < n; i++) {
        x[i] = x_new[i];
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &a[i][j]);
            a_copy[i][j] = a[i][j];
        }
        scanf("%lf", &b[i]);
        b_copy[i] = b[i];
    }
    
    gauss_slau();
    
    for (int i = 0; i < n; i++) {
        printf("%.10f\n", x[i]);
    }
    
    return 0;
}