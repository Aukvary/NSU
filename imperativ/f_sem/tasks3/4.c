#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int nums[10000];
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    int max_l = 0;
    int max_r = n - 1;
    int max = -2147483648;

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += nums[j];
            if (sum > max) {
                max = sum;
                max_l = i;
                max_r = j;
            }
        }
    }

    printf("%d %d %d", max_l, max_r, max);

    return 0;
}