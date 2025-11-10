#include <stdio.h>
#include <stdlib.h>

#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct { int idx; int val; } pair;

pair bin_search(int* nums, int len, int target) {
    int l = 0;
    int r = len - 1;
    
    int idx = 0;
    int val = ABS(target - nums[0]);
    
    while (l <= r) {
        int m = l + (r - l) / 2;
        
        int dif = ABS(target - nums[m]);
        
        if (dif < val) {
            val = dif;
            idx = m;
        }
        
        if (nums[m] == target) {
            break;
        } else if (nums[m] < target) {
            l = m + 1;  
        } else {
            r = m - 1;  
        }
    }
    
    return (pair){ idx, val };
}

int main() {
    FILE* in = fopen("input.txt", "r");

    int n;
    fscanf(in, "%d", &n);

    int* nums = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        fscanf(in, "%d", nums + i);

    int q;
    fscanf(in, "%d", &q);

    for (int i = 0; i < q; i++) {
        int a;
        fscanf(in, "%d", &a);
        pair res = bin_search(nums, n, a);
        printf("%d %d\n", res.idx, res.val);
    }
    
    return 0;
}