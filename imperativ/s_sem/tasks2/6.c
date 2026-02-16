#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 105  

int gauss_solve(double m[SIZE][SIZE], double b[SIZE], int n) {
    double a[SIZE][SIZE + 1];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = m[i][j];
        }
        a[i][n] = b[i];
    }

    for (int col = 0; col < n; col++) {
        int pivot_row = col;
        double max_val = fabs(a[col][col]);
        for (int row = col + 1; row < n; row++) {
            if (fabs(a[row][col]) > max_val) {
                max_val = fabs(a[row][col]);
                pivot_row = row;
            }
        }

        if (max_val < 1e-12) {
            return -1; 
        }

        if (pivot_row != col) {
            for (int k = 0; k <= n; k++) {
                double temp = a[col][k];
                a[col][k] = a[pivot_row][k];
                a[pivot_row][k] = temp;
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

int main() {
    freopen("input.txt", "r", stdin);
    
    int m;  
    double x[SIZE];
    double y[SIZE];
    
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%lf %lf", &x[i], &y[i]);
    }
    
    int n = m;  
    
    double a[SIZE][SIZE];
    double ata[SIZE][SIZE];
    double aty[SIZE];
    double c[SIZE];            
    
    for (int i = 0; i < m; i++) {
        double x_pow = 1.0;
        for (int j = 0; j < n; j++) {
            a[i][j] = x_pow;
            x_pow *= x[i];
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ata[i][j] = 0.0;
            for (int k = 0; k < m; k++) {
                ata[i][j] += a[k][i] * a[k][j];
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        aty[i] = 0.0;
        for (int k = 0; k < m; k++) {
            aty[i] += a[k][i] * y[k];
        }
    }
    
    for (int i = 0; i < n; i++) {
        c[i] = aty[i];
    }
    
    if (gauss_solve(ata, c, n) != 0) {
        n = (n > 5) ? 5 : n-1;
        for (int i = 0; i < m; i++) {
            printf("0.0 ");
        }
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        if (fabs(c[i]) < 1e-10) {
            c[i] = 0.0;
        }
        printf("%.6f ", c[i]);
    }
    printf("\n");
    
    return 0;
}