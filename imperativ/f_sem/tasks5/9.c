#include <stdio.h>
#include <stdlib.h>

long long f(long long* nums, int i, long long c) {
    return nums[i] + c * i;
}

int func(long long* nums, int n, long long c) {
    int l = 0;
    int r = n - 1;
    
    while (r - l > 2) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        
        long long f1 = f(nums, m1, c);
        long long f2 = f(nums, m2, c);
        
        if (f1 < f2) {
            r = m2 - 1;
        } else if (f1 > f2) {
            l = m1 + 1;
        } else {
            l = m1;
            r = m2;
        }
    }
    
    int index = l;
    long long best_val = f(nums, l, c);
    
    for (int i = l + 1; i <= r; i++) {
        long long current_val = f(nums, i, c);
        if (current_val < best_val) {
            best_val = current_val;
            index = i;
        }
    }
    
    return index;
}

int main() {
    FILE* in = fopen("input.txt", "r");

    int n;
    fscanf(in, "%d", &n);
    
    long long* ns = calloc(n, sizeof(long long));
    
    for (int i = 0; i < n; i++) {
        fscanf(in, "%lld", &ns[i]);
    }
    
    int q;
    fscanf(in, "%d", &q);
    
    for (int i = 0; i < q; i++) {
        long long c;
        fscanf(in, "%lld", &c);
        
        int result = func(ns, n, c);
        printf("%d\n", result);
    }
    
    return 0;
}