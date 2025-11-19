#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    long long x = *(long long*)a;
    long long y = *(long long*)b;
    return x - y;
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    int n;
    fscanf(in, "%d", &n);
    
    long long* arr = calloc(n, sizeof(long long));
    for (int i = 0; i < n; i++) {
        fscanf(in, "%lld", &arr[i]);
    }
    
    qsort(arr, n, sizeof(long long), cmp);
    
    long long sum = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            sum += arr[i];
        }
    }

    printf("%ld", sum);
    
    free(arr);
    return 0;
}