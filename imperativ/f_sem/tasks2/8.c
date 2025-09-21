#include <stdio.h>

int get_days(int m, int y) {
    switch(m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;

        case 4:
        case 6:
        case 9:
        case 11:
            return 30;

        default:
            return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0) ? 29 : 28;
    }
}

int main() {
    int d, m, y, k;

    scanf("%d %d %d %d", &d, &m, &y, &k);

    d += k;
    
    while (d > get_days(m, y)) {
        d -= get_days(m, y);
        m++;
        
        if (m > 12) {
            m = 1;
            y++;
        }
    }

    printf("%d %d %d", d, m, y);

    return 0;
}