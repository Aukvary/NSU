#include <stdio.h>
#include <string.h>

void reverse(char* s, size_t n) {
    size_t l = 0;
    size_t r = n - 1;

    while (l < r) {
        char temp = s[l];
        s[l] = s[r];
        s[r] = temp;
        l++;
        r--;
    }
}

int main() {
    int n;
    FILE* in = fopen("input.txt", "r");
    fscanf(in, "%d\n", &n);

    for (int i = 0; i < n; i++) {
        char s[101];
        fscanf(in, "%s", s);
        reverse(s, strlen(s));
        printf("%s\n", s);
    }


    return 0;
}