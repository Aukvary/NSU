#include <stdint.h>

int64_t Sum(int l, int r);
extern int n;

int Query(int l, int64_t sum) {
    int r;
    for (r = l; r < n; r++) {  
        if (r < n && Sum(l, r + 1) > sum) {
            break;
        }
    }
    return r;
}