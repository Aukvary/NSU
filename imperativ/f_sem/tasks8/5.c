#include <stdio.h>
#include <stdlib.h>

#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct { int idx; long long val; } pair;

pair bin_search(int* nums, int len, long long target) {
    int l = 0, r = len;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (nums[m] < target) l = m + 1;
        else r = m;
    }

    int pos = l;
    int idx;
    int dif;

    if (pos == 0) {
        idx = 0;
        dif = abs(nums[0] - target);
    } else if (pos == len) {
        idx = len - 1;
        dif = abs(nums[len - 1] - target);
    } else {
        int dif_r = abs(nums[pos] - target);
        int dif_l = abs(nums[pos - 1] - target);
        if (dif_r < dif_l) { 
            idx = pos; 
            dif = dif_r; 
        }
        else if (dif_l < dif_r) { 
            idx = pos - 1; 
            dif = dif_l; 
        }
        else { 
            idx = pos; 
            dif = dif_r; 
        } 
    }

    return (pair){idx, dif};
}

int main() {
    FILE* in = fopen("input.txt", "r");

    int n;
    fscanf(in, "%d", &n);

    int* nums = calloc(n, sizeof(int));

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