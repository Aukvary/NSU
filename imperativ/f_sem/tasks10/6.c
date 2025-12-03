#include <stdio.h>
#include <stdlib.h>

typedef long long i64;

int main() {
    freopen("input.txt", "r", stdin);

    i64 k;
    if (scanf("%lld", &k) != 1) return 0;

    int* nums = NULL;
    int count = 0;
    int size = 0;
    int val;

    while (scanf("%d", &val) == 1) {
        if (count == size) {
            size = size ? size * 2 : 10;
            nums = realloc(nums, size * sizeof(int));
        }
        nums[count++] = val;
    }

    int* right = calloc(count, sizeof(int));

    int** next = calloc(count, sizeof(int *));
    int* next_size = calloc(count, sizeof(int));
    int* next_capacity = calloc(count, sizeof(int));
    
    int* stack = calloc(count, sizeof(int));
    int top = 0;

    for (int i = 0; i < count; i++) {
        right[i] = count;
        next[i] = NULL;
    }

    for (int i = 0; i < count; i++) {
        while (top > 0 && nums[stack[top - 1]] < nums[i]) {
            right[stack[top - 1]] = i;
            top--;
        }
        if (top > 0) {
            int u = stack[top - 1];
            if (next_size[u] == next_capacity[u]) {
                int nc = next_capacity[u] ? next_capacity[u] * 2 : 10;
                next[u] = realloc(next[u], nc * sizeof(int));
                next_capacity[u] = nc;
            }
            next[u][next_size[u]++] = i;  
        }
        stack[top++] = i;
    }

    free(stack);

    int* dq = calloc(count, sizeof(int)); 
    int head = 0;
    int tail = 0;

    i64 res = 0;
    i64 sum = 0;  
    int l = 0;

    for (int r = 0; r < count; r++) {
        while (tail > head && nums[dq[tail - 1]] <= nums[r]) 
            tail--;


        dq[tail++] = r;

        int maxv = nums[dq[head]];

        if (maxv > nums[r]) {
            sum += (i64)(maxv - nums[r]); 
        }

        
        while (sum > k) {
            int out = nums[l];
            int sz = next_size[l];
            int *gl = next[l];

            
            for (int idx = 0; idx < sz; idx++) {
                int i = gl[idx];
                if (i > r) break;  

                i64 diff = (i64)out - nums[i];
                if (diff <= 0) continue;

                int rb = right[i];
                if (rb > r + 1) rb = r + 1;
                i64 len = (i64)(rb - i);
                if (len > 0)
                    sum -= diff * len;
            }

            l++;
            
            while (tail > head && dq[head] < l) head++;
        }

        
        res += (i64)(r - l + 1);
    }

    printf("%lld\n", res);
    return 0;
}
