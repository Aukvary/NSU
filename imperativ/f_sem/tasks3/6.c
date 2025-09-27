#include <stdio.h>

char bin_search(int* a, int n, int target) {
    int l = 0;
    int r = n - 1;

    while (l <= r) {
        int m = l + (r - l) / 2;

        if (a[m] == target)
            return 1;
        else if (a[m] > target)
            r = m - 1;
        else 
            l = m + 1;
            
    }

    return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int res[n];
    int ns[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &ns[i]);
        res[i] = 0;
    }
    
    int m;
    scanf("%d", &m);

    int ms[m];
    for (int i = 0; i < m; i++)
        scanf("%d", &ms[i]);

    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && ns[j] < ns[j - 1]; j--) {
            int temp = ns[j - 1];
            ns[j - 1] = ns[j];
            ns[j] = temp;
        }
    }
    
    for (int i = 1; i < m; i++) {
        for (int j = i; j > 0 && ms[j] < ms[j - 1]; j--) {
            int temp = ms[j - 1];
            ms[j - 1] = ms[j];
            ms[j] = temp;
        }
    }

    int len = 0;

    for (int i = 0; i < n; i++) {
        if (bin_search(ms, m, ns[i]))
            continue;
        if (len != 0 && res[len - 1] == ns[i])
            continue;
        res[len] = ns[i];
        len++;
    }

    printf("%d\n", len);

    for (int i = 1; i < len; i++) {
        for (int j = i; j > 0 && res[j] < res[j - 1]; j--) {
            int temp = res[j - 1];
            res[j - 1] = res[j];
            res[j] = temp;
        }
    }

    for (int i = 0; i < len; i++) {
        printf("%d ", res[i]);
    }

    return 0;
}