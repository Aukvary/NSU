#include <math.h>
#include <stdio.h>

#define SIZE 200

int n;

double a[SIZE][SIZE];
double b[SIZE];
double x[SIZE];

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