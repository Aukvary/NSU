#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int find_b(int a, int m) {
    int m0 = m;
        int y = 0, x = 1;
        
        if (m == 1)
            return 0;
        
        while (a > 1) {
            int q = a / m;
            int t = m;
            
            m = a % m;
            a = t;
            t = y;
            
            y = x - q * y;
            x = t;
        }
        
        if (x < 0)
            x += m0;
        
        return x;
}

int main(void) {
    freopen("input.txt", "r", stdin);
    
    int t;
    int m;
    int a;

    scanf("%d", &t);
    scanf("%d", &m);
    
    while(t--) {
        scanf("%d", &a);
        
        if (gcd(a, m) != 1) {
            printf("-1\n");
            continue;
        }
        
        
        printf("%d\n", find_b(a, m));
    }

    return 0;
}
