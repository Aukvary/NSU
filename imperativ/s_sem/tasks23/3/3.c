#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    int *nums = (int *)malloc(n * sizeof(int));
    long long total_sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        total_sum += nums[i];
    }

    if (total_sum % 2 != 0) {
        printf("false\n");
    } else {
        int target = (int)(total_sum / 2);
        unsigned char *dp = calloc(target + 1, sizeof(unsigned char));
        dp[0] = 1;

        for (int i = 0; i < n; i++) {
            int val = nums[i];
            for (int j = target; j >= val; j--) {
                if (dp[j - val]) {
                    dp[j] = 1;
                }
            }
            if (dp[target]) break;
        }

        if (dp[target]) {
            printf("true\n");
        } else {
            printf("false\n");
        }
        free(dp);
    }

    free(nums);
    return 0;
}