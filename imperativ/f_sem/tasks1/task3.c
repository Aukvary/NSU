#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int count = 0;

    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);

        count += 2;

        if (a % 10 == 9) {
            count -= 1;
        } else if (a % 10 == 0) {
            a /= 10;
            count += 1;
            while (a > 0) {
                if (a % 10 == 0) 
                    count += 1;
                a /= 10;
            }
        }
    }

    printf("%d\n", count);
}

// int main() {
//     int n;
//     scanf("%d", &n);
    
//     int count = 0;
    
//     for (int i = 0; i < n; i++) {
//         int a;
//         scanf("%d", &a);
        
//         a--;
//         count += 2;
        
//         while (a > 0 && a % 10 == 9) {
//             count++;
//             a /= 10;
//         }
//     }
    
//     printf("%d\n", count);
//     return 0;
// }