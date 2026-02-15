#include <stdio.h>
#include <math.h>

#define SIZE 100
#define EPS 1e-10

int n;
double x[SIZE], y[SIZE];
double g[SIZE][SIZE];
double f[SIZE];

double basis_func(double x_val, int j) {
    if (j == 0) return 1.0;
    double res = 1.0;
    for (int k = 0; k < j; k++) {
        res *= x_val;
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    
    scanf("%d", &n);
    
    double x_mean = 0, x_scale = 1;
    double x_norm[SIZE];
    
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &x[i], &y[i]);
        x_mean += x[i];
    }
    x_mean /= n;
    
    for (int i = 0; i < n; i++) {
        x_norm[i] = x[i] - x_mean;
    }
    
    x_scale = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(x_norm[i]) > x_scale) {
            x_scale = fabs(x_norm[i]);
        }
    }
    if (x_scale < EPS) x_scale = 1;
    
    for (int i = 0; i < n; i++) {
        x_norm[i] /= x_scale;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                g[i][j] += basis_func(x_norm[k], i) * basis_func(x_norm[k], j);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        f[i] = 0.0;
        for (int k = 0; k < n; k++) {
            f[i] += basis_func(x_norm[k], i) * y[k];
        }
    }
    
    double a[SIZE][SIZE + 1];
    double c[SIZE] = {0};
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = g[i][j];
        }
        a[i][n] = f[i];
    }
    
    for (int i = 0; i < n; i++) {
        int max_row = i, max_col = i;
        double max_val = fabs(a[i][i]);
        
        for (int r = i; r < n; r++) {
            for (int c = i; c < n; c++) {
                if (fabs(a[r][c]) > max_val) {
                    max_val = fabs(a[r][c]);
                    max_row = r;
                    max_col = c;
                }
            }
        }
        
        if (max_val < EPS) {
            continue;
        }
        
        if (max_row != i) {
            for (int j = i; j <= n; j++) {
                double temp = a[i][j];
                a[i][j] = a[max_row][j];
                a[max_row][j] = temp;
            }
        }
        
        if (max_col != i) {
            for (int r = 0; r < n; r++) {
                double temp = a[r][i];
                a[r][i] = a[r][max_col];
                a[r][max_col] = temp;
            }
        }
        
        double divisor = a[i][i];
        for (int j = i; j <= n; j++) {
            a[i][j] /= divisor;
        }
        
        for (int k = 0; k < n; k++) {
            if (k != i && fabs(a[k][i]) > EPS) {
                double factor = a[k][i];
                for (int j = i; j <= n; j++) {
                    a[k][j] -= factor * a[i][j];
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        c[i] = a[i][n];
    }
    
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%.10f", c[i]);
    }
    printf("\n");
    
    return 0;
}