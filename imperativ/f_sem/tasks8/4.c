#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATTERN "GGGGCC"
#define SIZE 6

void cacl_prefs(char* pattern, int* prefs) {
    int len = 0;
    prefs[0] = 0;
    int i = 1;
    
    while (i < SIZE) {
        if (pattern[i] == pattern[len]) {
            len++;
            prefs[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = prefs[len - 1];
            } else {
                prefs[i] = 0;
                i++;
            }
        }
    }
}

int main() {
    FILE* in = fopen("input.txt", "r");
    
    int t;
    fscanf(in, "%d", &t);
    
    int prefs[SIZE];
    cacl_prefs(PATTERN, prefs);
    
    int row_count = 0;
    int j = 0;
    int c;
    
    while ((c = fgetc(in)) != EOF && row_count < 31) {
        while (j > 0 && c != PATTERN[j]) {
            j = prefs[j - 1];
        }
        
        if (c == PATTERN[j]) {
            j++;
        }
        
        if (j == SIZE) {
            row_count++;
            j = prefs[j - 1];
        }
    }
    
    if (row_count > 30) {
        printf("Pathogenic");
    } else {
        printf("Non-pathogenic");
    }
    
    return 0;
}


// #include <stdio.h>
// #include <string.h>

// #define PATTERN "GGGGCC"

// int main() {
//     FILE* in = fopen("input.txt", "r");
//     int t;
//     fscanf(in, "%d", &t);
    
//     char buf[7] = {0};
//     int row_count = 0;
    
//     for (int i = 0; i < 6; i++) {
//         int c = fgetc(in);
//         if (c == EOF) break;
//         buf[i] = c;
//     }
    
//     if (strcmp(buf, PATTERN) == 0) {
//         row_count = 1;
//     }
    
//     int c;
//     while ((c = fgetc(in)) != EOF && row_count < 31) {
//         memmove(buf, buf + 1, 5);
//         buf[5] = c;
        
//         if (strcmp(buf, PATTERN) == 0) {
//             row_count++;
//         }
//     }
    
//     if (row_count > 30) {
//         printf("Pathogenic");
//     } else {
//         printf("Non-pathogenic");
//     }
    
//     return 0;
// }