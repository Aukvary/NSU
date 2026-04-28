#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    if (scanf("%d", &n) != 1) return 0;

    int candidate = 0;
    int count = 0;
    int current;

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &current) != 1) break;
        if (count == 0) {
            candidate = current;
            count = 1;
        } else if (current == candidate) {
            count++;
        } else {
            count--;
        }
    }

    if (n <= 0) {
        printf("NO\n");
        return 0;
    }

    freopen("input.txt", "r", stdin);
    scanf("%d", &n); 

    int actual_count = 0;
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &current) != 1) break;
        if (current == candidate) {
            actual_count++;
        }
    }

    if (actual_count > n / 2) {
        printf("YES\n%d\n", candidate); 
    } else {
        printf("NO\n");
    }

    return 0;
}