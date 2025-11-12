#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
    FILE* in = fopen("input.txt", "r");
    
    char buf[3000] = { 0 };
    int len = fread(buf, 1, sizeof(buf) - 1, in);
    buf[len] = '\0';
    
    int len1 = 0;
    while (len1 < len && buf[len1] != '\n') {
        len1++;
    }
    
    int len2 = len - len1 - 1; 
    
    char* num1 = buf;
    char* num2 = buf + len1 + 1;         
    
    while (len1 > 0 && (num1[len1-1] == '\n' || num1[len1-1] == '\r')) len1--;
    while (len2 > 0 && (num2[len2-1] == '\n' || num2[len2-1] == '\r')) len2--;
    
    int result_len = len1 + len2;
    int* result = calloc(3000, sizeof(int));
    
    for (int i = len1 - 1; i > -1; i--) {
        for (int j = len2 - 1; j > -1; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = result[i + j + 1] + mul;
            
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }
    
    int start_index = 0;
    while (start_index < result_len - 1 && result[start_index] == 0) {
        start_index++;
    }
    
    
    for (int i = start_index; i < result_len; i++) {
        printf("%d", result[i]);
    }
    
    free(result);
    return 0;
}