#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tokens_s {
    int num; 
    char** arr; 
} Tokens;

char isSep(const char c, const char* s) {
    while(*s) {
        if (c == *s) return 1;
        s++;
    }
    return 0;
}

int word_count(const char* str, const char* delims) {
    int n = 0;
    const char* s = str;
    while (*s) {
        while (*s && isSep(*s, delims))
            s++;
        
        if (!(*s)) break;
        
        n++;
        while (*s && !isSep(*s, delims)) 
            s++;
    }
    return n;
}

char* get_next(const char* str, const char* delims) {
    static char* source = NULL;
    static char* current = NULL;
    
    if (str != NULL) {
        if (source) free(source);
        source = malloc(strlen(str) + 1);
        strcpy(source, str);
        current = source;
    }
    
    if (current == NULL || *current == '\0')        return NULL;
    
    while (*current && isSep(*current, delims))     current++;
    
    if (*current == '\0')                           return NULL;
    
    char* start = current;
    
    while (*current && !isSep(*current, delims))    current++;
    
    if (*current) {
        *current = '\0';
        current++;
    }
    
    return start;
}

void tokensSplit(Tokens* tokens, const char* str, const char* delims) {
    int count = word_count(str, delims);
    if (!tokens->arr)
        tokens->arr = calloc(count, sizeof(char*));
    
    tokens->arr[0] = get_next(str, delims);
    
    for (int i = 1; i < count; i++) {
        tokens->arr[i] = get_next(NULL, delims);
    }
    
    tokens->num = count;
}

void tokensFree(Tokens *tokens) {
    if (!tokens->arr) return;

    if (tokens->arr) {
        free(tokens->arr);
        tokens->arr = NULL;
    }
    tokens->num = 0;
}

int main() {
    Tokens t = { 0 };

    FILE* in = fopen("input.txt", "r");
    char buf[1000001] = { 0 };
    fgets(buf, sizeof(buf), in);

    tokensSplit(&t, buf, ":;,.\n\r");

    printf("%d\n", t.num);
    for (int i = 0; i < t.num; i++) {
        printf("%s\n", t.arr[i]);
    }

    tokensFree(&t);
    return 0;
}