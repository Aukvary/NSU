#include <stdio.h>

int main() {
    int n;

    FILE* in = fopen("input.txt", "r");

    fscanf(in, "%d", &n);
    if (n == 0 || n == 1) {
        printf("0");
        return 0;
    }

    int sizes[100001], l[100001], r[100001];

    for (int i = 0; i < n; i++) 
        fscanf(in, "%d", &sizes[i]);

    l[0] = sizes[0];
    for (int i = 1; i < n; i++) 
        l[i] = (sizes[i] > l[i - 1]) ? sizes[i] : l[i - 1];
    
    r[n - 1] = sizes[n - 1];
    for (int i = n - 2; i >= 0; i--) 
        r[i] = (sizes[i] > r[i + 1]) ? sizes[i] : r[i + 1];

    long long count = 0;
    for (int i = 0; i < n; i++) {
        int min = (l[i] < r[i]) ? l[i] : r[i];
        count += min - sizes[i];
    }

    printf("%lld", count);

    return 0;
}