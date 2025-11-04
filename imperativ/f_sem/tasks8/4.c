#include <stdio.h>
#include <string.h>

const char* pattern = "GGGGCC";

int main() {
    FILE* in = fopen("input.txt", "r");
    int t;
    fscanf(in, "%d", &t);
    
    char buf[7] = {0};
    int row_count = 0;
    
    for (int i = 0; i < 6; i++) {
        int c = fgetc(in);
        if (c == EOF) break;
        buf[i] = c;
    }
    
    if (strcmp(buf, pattern) == 0) {
        row_count = 1;
    }
    
    int c;
    while ((c = fgetc(in)) != EOF) {
        memmove(buf, buf + 1, 5);
        buf[5] = c;
        
        if (strcmp(buf, pattern) == 0) {
            row_count++;
        }

        if (row_count == 31) break;
    }
    
    if (row_count > 30) {
        printf("Pathogenic");
    } else {
        printf("Non-pathogenic");
    }
    
    return 0;
}