#include <stdio.h>

#define MOD 1000000007
#define SIZE 300

int n;
int k;
int p;
int a[SIZE][SIZE] = {0};
int b[SIZE] = {0};
int rank;

int pow_mod(int x, int power, int mod) {
    long long res = 1;
    long long base = x % mod;
    
    while (power > 0) {
        if (power & 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        power >>= 1;
    }
    
    return (int)res;
}

int inv_mod(int x, int mod) {
    return pow_mod(x, mod - 2, mod);
}

int gauss() {
    int i;
    int j;
    int row = 0;
    int col = 0;
    int max_row;
    
    while (row < k && col < n) {
        max_row = -1;
        for (i = row; i < k; i++) {
            if (a[i][col] != 0) {
                max_row = i;
                break;
            }
        }
        
        if (max_row == -1) {
            col++;
            continue;
        }
        
        if (max_row != row) {
            for (j = col; j < n; j++) {
                int temp = a[row][j];
                a[row][j] = a[max_row][j];
                a[max_row][j] = temp;
            }
            int temp = b[row];
            b[row] = b[max_row];
            b[max_row] = temp;
        }
        
        int inv = inv_mod(a[row][col], p);
        for (j = col; j < n; j++) {
            a[row][j] = (int)((long long)a[row][j] * inv % p);
        }
        b[row] = (int)((long long)b[row] * inv % p);
        
        for (i = 0; i < k; i++) {
            if (i != row && a[i][col] != 0) {
                int factor = a[i][col];
                for (j = col; j < n; j++) {
                    a[i][j] = (a[i][j] - (int)((long long)factor * a[row][j] % p) + p) % p;
                }
                b[i] = (b[i] - (int)((long long)factor * b[row] % p) + p) % p;
            }
        }
        
        row++;
        col++;
    }
    
    rank = row;
    
    for (i = rank; i < k; i++) {
        int all_zero = 1;
        for (j = 0; j < n; j++) {
            if (a[i][j] != 0) {
                all_zero = 0;
                break;
            }
        }
        if (all_zero && b[i] != 0) {
            return -1;  
        }
    }
    
    return rank;
}

int main() {
    freopen("input.txt", "r", stdin);
    
    scanf("%d %d %d", &n, &k, &p);
    
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
        scanf("%d", &b[i]);
    }
    
    int result = gauss();
    
    if (result == -1) {
        printf("0\n");
    } else if (rank == n) {
        int x[SIZE] = {0};
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                if (j < rank && a[j][i] == 1) {
                    x[i] = b[j];
                    break;
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            printf("%d\n", x[i]);
        }
    } else {
        int free_vars = n - rank;
        long long count = 1;
        
        for (int i = 0; i < free_vars; i++) {
            count = (count * p) % MOD;
        }
        
        printf("%lld\n", count);
    }
    return 0;
}