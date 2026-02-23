#include <stdint.h>
#include <stdlib.h>

static int64_t* presum = NULL;


void Init(const int *arr, int n) {
    presum = malloc((n + 1) * sizeof(int64_t));
    
    presum[0] = 0;
    for (int i = 1; i <= n; i++) {
        presum[i] = presum[i - 1] + arr[i - 1];  
    }
}

int64_t Sum(int l, int r) {    
    return presum[r] - presum[l];
}