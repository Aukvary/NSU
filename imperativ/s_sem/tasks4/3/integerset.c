#include <string.h>
#include <stdlib.h>
#include "integerset.h"

static int cmp(const void* a, const void* b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

IntegerSet* CreateSet(int* nums, int count) {
    if (count == 0) {
        IntegerSet* set = malloc(sizeof(IntegerSet));
        set->count = 0;
        return set;
    }
    
    IntegerSet* set = malloc(sizeof(IntegerSet) + count * sizeof(int));
    set->count = count;

    int* tmp = malloc(count * sizeof(int));
    memcpy(tmp, nums, sizeof(int) * count);
    qsort(tmp, count, sizeof(int), cmp);

    set->nums[0] = tmp[0];
    for (int i = 1; i < count; i++) {
        if (tmp[i] == tmp[i - 1]) {
            free(tmp);
            free(set);
            return NULL;
        }
        set->nums[i] = tmp[i];
    }

    free(tmp);

    return set;
}

int IsInSet(IntegerSet* set, int num) {
    if (!set) {
        return 0;
    }

    int l = 0;
    int r = set->count - 1;

    while (l <= r) {
        int m = l + (r - l) / 2;
        if (set->nums[m] == num) {
            return 1;
        } else if (set->nums[m] < num) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    return 0;
}