#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 100

typedef struct {
    double p;
    double s; 
    double l;
} timeComplexity;

timeComplexity parse(const char* str) {
    timeComplexity result = {1.0, 0.0, 0.0};
    
    const char* ptr = strstr(str, "O(");
    if (!ptr) 
        return result;
    ptr += 2;
    
    if (strstr(ptr, "1)") == ptr) 
        return result;
    
    char buffer[SIZE];
    strncpy(buffer, ptr, strcspn(ptr, ")"));
    buffer[strcspn(ptr, ")")] = '\0';
    
    char* token = strtok(buffer, " ");
    while (token) {
        if (strstr(token, "^N")) {
            char num[50];
            strncpy(num, token, strcspn(token, "^"));
            num[strcspn(token, "^")] = '\0';
            result.p = atof(num);
        }
        else if (token[0] == 'N' && strchr(token, '^')) {
            char* caret = strchr(token, '^');
            result.s = atof(caret + 1);
        }
        else if (strcmp(token, "N") == 0) {
            result.s = 1.0;
        }
        else if (strstr(token, "logN^")) {
            char* caret = strchr(token, '^');
            result.l = atof(caret + 1);
        }
        else if (strcmp(token, "logN") == 0) {
            result.l = 1.0;
        }
        
        token = strtok(NULL, " ");
    }
    
    return result;
}

int cmp(const timeComplexity* a, const timeComplexity* b) {
    if (fabs(a->p - b->p) > 1e-9) 
        return (a->p > b->p) ? 1 : -1;
    
    if (fabs(a->s - b->s) > 1e-9) 
        return (a->s > b->s) ? 1 : -1;
    
    if (fabs(a->l - b->l) > 1e-9) 
        return (a->l > b->l) ? 1 : -1;
    
    return 0;
}

int main() {
    int n;
    FILE* in = fopen("input.txt", "r");
    fscanf(in, "%d\n", &n);
    
    char buf1[SIZE], buf2[SIZE];
    
    for (int i = 0; i < n; i++) {
        fgets(buf1, SIZE, in);
        fgets(buf2, SIZE, in);
        
        buf1[strcspn(buf1, "\n")] = 0;
        buf2[strcspn(buf2, "\n")] = 0;
        
        timeComplexity a1 = parse(buf1);
        timeComplexity a2 = parse(buf2);
        
        printf("%d\n", cmp(&a1, &a2));
    }
    
    return 0;
}