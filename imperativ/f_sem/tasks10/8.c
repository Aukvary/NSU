#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 100000

int main() {
    freopen("input.txt", "r", stdin);
    
    int k;
    int n = 0;
    int nums[SIZE];
    
    scanf("%d", &k);
    while (scanf("%d", &nums[n]) != EOF) {
        n++;
    }
    
    long long dp[SIZE];
    int queue[SIZE];
    int front = 0;
    int back = -1;
    
    dp[0] = nums[0];
    queue[++back] = 0;
    
    for (int i = 1; i < n; i++) {
        while (front <= back && queue[front] < i - k) {
            front++;
        }
        
        dp[i] = nums[i] + dp[queue[front]];
        
        while (front <= back && dp[queue[back]] <= dp[i]) {
            back--;
        }
        
        queue[++back] = i;
    }
    
    printf("%lld\n", dp[n-1]);
    
    return 0;
}