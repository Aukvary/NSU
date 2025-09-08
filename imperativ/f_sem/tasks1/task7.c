#include <stdio.h>

int main(void) {
    int n;
    int m/*номер*/, p/*подъезд*/, k/*этаж*/, l/*кол-во этажей*/;

    scanf("%d", &n);
    scanf("%d %d %d %d", &m, &p, &k, &l);

    float g = l * (p - 1) + k - 1;
    int c;
    
    for (int i = 1; i < 0x7FFFFFFF; i++) {
        float j = (m - i) / g;
        
        if (j == (int)j) {
            c = j;
            break;            
        }
    }

    int i;
    for (i = 1; i * l * c < n; i++);

    int j;
    for (j = 1; (i-1) * l * c + j * c <= n; j++);

    printf("%d %d", i, j - 1);
}