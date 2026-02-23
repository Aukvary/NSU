#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int n;

void Init(const int *arr, int n);
int64_t Sum(int l, int r);
int Query(int l, int64_t sum);

int main() {
    freopen("input.txt", "r", stdin);

    int m;
    scanf("%d %d", &n, &m);
    int* arr = malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    Init(arr, n);
    
    for (int i = 0; i < m; i++) {
        int l;
        int64_t s;
        scanf("%d %lld", &l, &s);
        
        int r = Query(l, s);
        
        printf("%d\n", r);
    }
    
    return 0;
}