#include <stdio.h>

int main() {
    int n;
    char data[27] = { 0 };    
    FILE* in = fopen("input.txt", "r");
    fscanf(in, "%d\n", &n);
    for (int i = 0; i < n; i++) {
        fscanf(in, "%c ", &data[i]);
    }

    printf("%d", n);
    printf("%s", data);
    return 0;
}