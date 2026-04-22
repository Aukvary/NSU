#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    int slow = 0;
    int fast = 0;

    int* nums = malloc((n + 1) * sizeof(int));
    for (int i = 0; i < n + 1; i++) {
        scanf("%d", &nums[i]);
    }

    slow = nums[0];
    fast = nums[nums[0]];

    while (slow != fast) {
        slow = nums[slow];
        fast = nums[nums[fast]];
    }

    fast = 0;
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }

    printf("%d\n", slow);

    free(nums);
    return 0;
}