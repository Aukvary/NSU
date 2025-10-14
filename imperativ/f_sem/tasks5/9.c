#include <stdio.h>
#include <stdlib.h>

long long f(long long* nums, int i, long long c) {
    return nums[i] + c * i;
}

int func(long long* nums, int n, long long c) {
    int res = 0;
    long long mx = f(nums, 0, c);
    
    for (int i = 0; i < n; i++) {
        long long cur = f(nums, i, c);
        if (cur < mx) {
            mx = cur;
            res = i;
        }
    }
    
    return res;
}

int main() {
    FILE* in = fopen("input.txt", "r");

    int n;
    fscanf(in, "%d", &n);
    
    long long* nums = calloc(n, sizeof(long long));
    
    for (int i = 0; i < n; i++) {
        fscanf(in, "%lld", &nums[i]);
    }
    
    int q;
    fscanf(in, "%d", &q);
    
    for (int i = 0; i < q; i++) {
        long long c;
        fscanf(in, "%lld", &c);
        
        int result = func(nums, n, c);
        printf("%d\n", result);
    }
    
    return 0;
}