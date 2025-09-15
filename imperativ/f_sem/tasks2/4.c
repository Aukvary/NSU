#include <stdio.h>

#define END(arg) printf(#arg); return 0;


int main() {
    int a1, a2;
    int b1, b2;
    int c1, c2;

    scanf("%d %d %d %d %d %d", &a1, &a2, &b1, &b2, &c1, &c2);

        if (b1 + c1 <= a1 && b2 <= a2 && c2 <= a2)
            END(YES)
            
        if (b1 + c1 <= a2 && b2 <= a1 && c2 <= a1)
            END(YES)
            
        if (b1 + c2 <= a1 && b2 <= a2 && c1 <= a2)
            END(YES)
            
        if (b1 + c2 <= a2 && b2 <= a1 && c1 <= a1)
            END(YES)
            
        if (b2 + c1 <= a1 && b1 <= a2 && c2 <= a2)
            END(YES)
            
        if (b2 + c1 <= a2 && b1 <= a1 && c2 <= a1)
            END(YES)
            
        if (b2 + c2 <= a1 && b1 <= a2 && c1 <= a2)
            END(YES)
            
        if (b2 + c2 <= a2 && b1 <= a1 && c1 <= a1)
            END(YES)
            

    END(NO)
}