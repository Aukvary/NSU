#include <stdio.h>
#include <stdlib.h>

int bin_search(int* nums, int len, int target) {
    int l = 0;
    int r = len - 1;
    int result = -1;

    while (l <= r) {
        int m = l + (r - l) / 2;  

        if (nums[m] == target) {
            result = m;  
        } else if (nums[m] < target) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    return result;
}

int main() {
    FILE* in = fopen("input.txt", "r");
    
    int n;
    fscanf(in, "%d", &n);

    int* nums = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(in, "%d", &nums[i]);
    }
    
    int q;
    fscanf(in, "%d", &q);  
    
    int r = 0;  
    
    for (int i = 0; i < q; i++) {
        int x;
        fscanf(in, "%d", &x);
        
        x += r;
        r = bin_search(nums, n, x);  
        
        printf("%d\n", r);
    }
    
    free(nums);
    return 0;
}