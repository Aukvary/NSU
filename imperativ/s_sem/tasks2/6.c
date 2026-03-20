#include <stdio.h>
#include <math.h>

#define CHUNK_SIZE 105

int gauss_solve(double m[CHUNK_SIZE][CHUNK_SIZE], double b[CHUNK_SIZE], int n) {
    double a[CHUNK_SIZE][CHUNK_SIZE + 1];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = m[i][j];
        }
        a[i][n] = b[i];
    }

    for (int col = 0; col < n; col++) {
        int p_row = col;
        double max_val = fabs(a[col][col]);
        for (int row = col + 1; row < n; row++) {
            if (fabs(a[row][col]) > max_val) {
                max_val = fabs(a[row][col]);
                p_row = row;
            }
        }

        if (max_val < 1e-12) {
            return -1;
        }

        if (p_row != col) {
            for (int k = 0; k <= n; k++) {
                double tmp = a[col][k];
                a[col][k] = a[p_row][k];
                a[p_row][k] = tmp;
            }
        }

        double pivot = a[col][col];
        for (int k = col; k <= n; k++) {
            a[col][k] /= pivot;
        }

        for (int row = col + 1; row < n; row++) {
            double factor = a[row][col];
            if (fabs(factor) > 1e-12) {
                for (int k = col; k <= n; k++) {
                    a[row][k] -= factor * a[col][k];
                }
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        b[i] = a[i][n];
        for (int j = i + 1; j < n; j++) {
            b[i] -= a[i][j] * b[j];
        }
    }

    return 0;
}

double power(double base, int exp) {
    double result = 1.0;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int main() {
    freopen("input.txt", "r", stdin);
    
    int n;
    double x[CHUNK_SIZE];
    double y[CHUNK_SIZE];
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &x[i], &y[i]);
    }
    
    double x_mean = 0.0;
    for (int i = 0; i < n; i++) {
        x_mean += x[i];
    }
    x_mean /= n;
    
    double x_max = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = fabs(x[i] - x_mean);
        if (diff > x_max) {
            x_max = diff;
        }
    }
    
    double xn[CHUNK_SIZE];
    for (int i = 0; i < n; i++) {
        xn[i] = (x[i] - x_mean) / x_max;
    }
    
    double a[CHUNK_SIZE][CHUNK_SIZE];
    double b[CHUNK_SIZE];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = power(xn[i], j);
        }
        b[i] = y[i];
    }
    
    if (gauss_solve(a, b, n) != 0) {
        for (int i = 0; i < n; i++) {
            printf("0.000000 ");
        }
    } else {
        double c[CHUNK_SIZE] = {0};
        
        for (int i = 0; i < n; i++) {
            double scale = 1.0;
            for (int k = 0; k < i; k++) {
                scale *= x_max;
            }
            
            for (int k = 0; k <= i; k++) {
                long long C = 1;
                for (int t = 1; t <= k; t++) {
                    C = C * (i - t + 1) / t;
                }
                
                double term = b[i] * C * power(-x_mean, i - k) / scale;
                
                if (k < n) {
                    c[k] += term;
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            if (fabs(c[i]) < 1e-8) {
                printf("0.000000 ");
            } else {
                printf("%.6f ", c[i]);
            }
        }
    }
    
    return 0;
}