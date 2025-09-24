#include <stdio.h>

int main() {
    int l, r, k;
    
    scanf("%d %d %d", &l, &r, &k);
    
    int count = 0;
    int range = r - l + 1;

    for (int i = 1; i <= range; i++) {
        for (int j = l; j <= r; j++) {
            int cur_count = 0;
            int cur = j;
            
            while (cur <= r) {
                if (cur >= l)
                    cur_count++;
                cur += i;
            }
            
            if (cur_count == k)
                count++;
        }
    }

    printf("%d", count);
}