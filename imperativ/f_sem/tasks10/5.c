#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
#define SIZE 100000

int main() {
    FILE* in = fopen("input.txt", "r");
    if (!in) return 1;

    int* nums = calloc(SIZE, sizeof(int));
    int count = 0;

    int* stack = calloc(SIZE, sizeof(int));
    int top = -1;
    int* left = calloc(SIZE, sizeof(int));
    int* right = calloc(SIZE, sizeof(int));

    int val;
    while (fscanf(in, "%d", &val) != EOF) {
        nums[count] = val;

        while (top > -1 && nums[stack[top]] >= val) {
            top--;
        }

        if (top < 0) {
            left[count] = -1;
        } else {
            left[count] = stack[top];
        }
        stack[++top] = count;
        count++;
    }
    fclose(in);

    long long* prefix = calloc(count + 1, sizeof(long long));
    prefix[0] = 0;
    for (int i = 0; i < count; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }

    top = -1;
    for (int i = count - 1; i >= 0; i--) {
        while (top > -1 && nums[stack[top]] > nums[i]) {
            top--;
        }

        if (top < 0) {
            right[i] = count;
        } else {
            right[i] = stack[top];
        }
        stack[++top] = i;
    }

    long long* P2 = calloc(count + 2, sizeof(long long));
    P2[0] = prefix[0];
    for (int k = 1; k <= count + 1; k++) {
        P2[k] = P2[k - 1] + prefix[k];
    }

    long long res = 0;
    for (int i = 0; i < count; i++) {
        int l = left[i] + 1;
        int r = right[i] - 1;
        long long count_l = i - l + 1;
        long long count_r = r - i + 1;

        long long term1 = count_l * (P2[r + 1] - P2[i]);
        long long term2 = count_r * (P2[i] - (l > 0 ? P2[l - 1] : 0));
        long long sum = term1 - term2;

        res = (res + nums[i] * sum) % MOD;
    }

    printf("%lld\n", res);

    free(nums);
    free(stack);
    free(left);
    free(right);
    free(prefix);
    free(P2);
    return 0;
}
