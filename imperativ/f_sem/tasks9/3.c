#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    long long x = *(long long*)a;
    long long y = *(long long*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    int n;
    fscanf(in, "%d", &n);
    
    long long *arr = malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        fscanf(in, "%lld", &arr[i]);
    }
    
    qsort(arr, n, sizeof(long long), compare);
    
    long long *unique = malloc(n * sizeof(long long));
    int k = 0;
    
    for (int i = 0; i < n; i++) {
        if (i == 0 || arr[i] != arr[i-1]) {
            unique[k++] = arr[i];
        }
    }
    
    fprintf(out, "%d\n", k);
    for (int i = 0; i < k; i++) {
        fprintf(out, "%lld\n", unique[i]);
    }
    
    free(arr);
    free(unique);
    return 0;
}