#include <stdio.h>
#include <stdlib.h>

#define SIZE 200005

typedef struct {
    long long val;
    int idx;
} Object;

Object d[SIZE];
int front = 0;
int back = 0;

void push_back(long long val, int idx) {
    while (back > front && d[back - 1].val <= val) {
        back--;
    }
    d[back].val = val;
    d[back].idx = idx;
    back++;
}

void pop_front(int idx) {
    while (front < back && d[front].idx < idx) {
        front++;
    }
}

long long get_max() {
    return d[front].val;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n;
    scanf("%d", &n);
    
    long long nums[SIZE];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &nums[i]);
    }
    
    char cmds[SIZE * 2];
    scanf("%s", cmds);
    
    for (int i = 0, l = 0, r = 0; i < 2 * n - 1; i++) {
        if (cmds[i] == 'R') {
            push_back(nums[r], r);
            r++;
        } else {
            l++;
            pop_front(l);
        }
        
        printf("%lld\n", get_max());
    }
    
    return 0;
}