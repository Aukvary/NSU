#include <stdio.h>



int main() {
    int n = 0;
    scanf("%d", &n);
    
    int nums[n];
    int enumerated[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        enumerated[i] = 0;
    }

    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && nums[j] < nums[j - 1]; j--) {
            int temp = nums[j - 1];
            nums[j - 1] = nums[j];
            nums[j] = temp;
        }
    }

    for (int i = 0; i < n; i++) {
        int count = 0;
        if (enumerated[i] == 1)
            continue;

        for (int j = i; j < n; j++) {
            if (nums[i] == nums[j]) {
                enumerated[j] = 1;
                count += 1;
            }
        }

        printf("%d: %d\n", nums[i], count);
    }

    return 0;
}