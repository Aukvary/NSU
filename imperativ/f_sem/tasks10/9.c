#include <stdio.h> 

#define SIZE 1000005 

typedef struct { 
    int a[4]; 
} Block; 

static char input[SIZE]; 
static Block stack[SIZE]; 

int check_open(char x) { 
    return (x == '(' || x == '[' || x == '{' || x == '<'); 
} 

int get_type(char x) { 
    switch (x) { 
        case '(': 
        case ')': return 0; 
        case '[': 
        case ']': return 1; 
        case '{': 
        case '}': return 2; 
        case '<': 
        case '>': return 3; 
    } 
    return 0; 
} 

int process_closing(int B[4], int *sp) { 
    while (1) { 
        int remaining = 0; 
        for (int i = 0; i < 4; ++i) 
            if (B[i] > 0) { remaining = 1; break; } 
        if (!remaining) return 1; 

        if (*sp == 0) return 0; 

        Block *top_block = &stack[*sp - 1]; 
        int matched = 0; 

        for (int i = 0; i < 4; ++i) { 
            if (top_block->a[i] > 0 && B[i] > 0) { 
                int min_val = top_block->a[i] < B[i] ? top_block->a[i] : B[i]; 
                top_block->a[i] -= min_val; 
                B[i] -= min_val; 
                matched += min_val; 
            } 
        } 

        if (!matched) return 0; 

        int is_empty = 1; 
        for (int i = 0; i < 4; ++i) 
            if (top_block->a[i] != 0) { is_empty = 0; break; } 
        if (is_empty) (*sp)--; 
    } 
} 

int main(void) { 
    int test_cases; 
    if (scanf("%d", &test_cases) != 1) return 0; 

    while (test_cases--) { 
        if (scanf("%s", input) != 1) return 0; 

        int length = 0; 
        while (input[length]) length++; 

        if (length % 2 == 1) { 
            printf("NIL\n"); 
            continue; 
        } 

        int valid = 1; 
        int stack_ptr = 0; 

        int current_open = check_open(input[0]); 
        int counts[4] = {0, 0, 0, 0}; 
        counts[get_type(input[0])]++; 

        for (int i = 1; i < length && valid; ++i) { 
            char ch = input[i]; 
            int now_open = check_open(ch); 

            if (now_open == current_open) { 
                counts[get_type(ch)]++; 
            } else { 
                if (current_open) { 
                    for (int j = 0; j < 4; ++j) 
                        stack[stack_ptr].a[j] = counts[j]; 
                    stack_ptr++; 
                } else { 
                    int temp[4]; 
                    for (int j = 0; j < 4; ++j) temp[j] = counts[j]; 
                    if (!process_closing(temp, &stack_ptr)) 
                        valid = 0; 
                } 

                current_open = now_open; 
                for (int j = 0; j < 4; ++j) counts[j] = 0; 
                counts[get_type(ch)]++; 
            } 
        } 

        if (valid) { 
            if (current_open) { 
                for (int j = 0; j < 4; ++j) 
                    stack[stack_ptr].a[j] = counts[j]; 
                stack_ptr++; 
            } else { 
                int temp[4]; 
                for (int j = 0; j < 4; ++j) temp[j] = counts[j]; 
                if (!process_closing(temp, &stack_ptr)) 
                    valid = 0; 
            } 
        } 

        if (!valid || stack_ptr != 0) printf("NIL\n"); 
        else printf("T\n"); 
    } 
    return 0; 
}