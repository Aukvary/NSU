#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define DECLARE_TYPES\
        X(char)\
        X(short)\
        X(int)\
        X(long)\
        X(float)\
        X(int64_t)\
        X(double)

typedef enum {
    #define X(t) type_##t,
    DECLARE_TYPES
    #undef X
} types;

const char* types_name[] = {
    #define X(t) #t,
    DECLARE_TYPES
    #undef X
};

const int type_sizes[][7] = {
    {1, 2, 2, 4, 4, 8, 8},
    {1, 2, 4, 4, 4, 8, 8},
    {1, 2, 4, 4, 4, 8, 8},
    {1, 2, 4, 8, 4, 8, 8}
};

typedef struct {
    types type;
    uint8_t is_ptr;
} field;

typedef struct {
    int size;
    int align;
} State;

field parse_field(const char* str) {
    field f = { .type = -1, .is_ptr = 0 };

    while(*str == ' ') str++;

    for (int i = 0; i < (sizeof(types_name) / sizeof(types_name[0])); i++) {
        size_t len = strlen(types_name[i]);
        
        if (strncmp(str, types_name[i], len) == 0) {
            char next_char = str[len];
            if (next_char == ' ' || next_char == '*' || next_char == ';' || next_char == '\n') {
                f.type = i;
                str += len;

                while (*str != ';' && *str != '\0' && *str != '\n') {
                    if (*str == '*') {
                        f.is_ptr = 1;
                        break;
                    }
                    str++;
                }
                break;
            }
        }
    }

    return f;
}

int get_size(field f, int mode) {
    if (f.is_ptr) {
        return mode < 2? 4 : 8;
    }
    return type_sizes[mode][f.type];
}

field fields[20];
int field_count = 0;

#define MAX_STATES 1000

typedef struct {
    State states[MAX_STATES];
    int count;
} StateList;

StateList dp[1<<10];

void add_state(StateList* list, State new_state) {
    for (int i = 0; i < list->count; i++) {
        if (list->states[i].size == new_state.size && list->states[i].align == new_state.align) {
            return;
        }
    }
    if (list->count < MAX_STATES) {
        list->states[list->count++] = new_state;
    }
}

void bitmask_dp(int model, int* min_size, int* max_size) {
    int n = field_count;
    int total_mask = (1 << n) - 1;
    
    for (int mask = 0; mask <= total_mask; mask++) {
        dp[mask].count = 0;
    }
    
    State initial = {0, 1};
    add_state(&dp[0], initial);
    
    for (int mask = 0; mask <= total_mask; mask++) {
        for (int state_idx = 0; state_idx < dp[mask].count; state_idx++) {
            State current = dp[mask].states[state_idx];
            
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) continue;
                
                int new_mask = mask | (1 << i);
                field f = fields[i];
                int size = get_size(f, model);
                int alignment = size;
                
                int padding = (alignment - (current.size % alignment)) % alignment;
                int new_size = current.size + padding + size;
                int new_align = (alignment > current.align) ? alignment : current.align;
                
                State new_state = {new_size, new_align};
                add_state(&dp[new_mask], new_state);
            }
        }
    }
    
    *min_size = 1000000000;
    *max_size = 0;
    
    for (int state_idx = 0; state_idx < dp[total_mask].count; state_idx++) {
        State current = dp[total_mask].states[state_idx];
        int final_padding = (current.align - (current.size % current.align)) % current.align;
        int total_size = current.size + final_padding;
        
        if (total_size < *min_size) *min_size = total_size;
        if (total_size > *max_size) *max_size = total_size;
    }
}

int main() {
    FILE* in = fopen("input.txt", "r");
    if (!in) {
        printf("Cannot open input file\n");
        return 1;
    }

    char buf[100];

    fgets(buf, sizeof(buf), in);
    
    while (fgets(buf, sizeof(buf), in)) {
        if (strstr(buf, "}") != NULL) break;
        
        if (strlen(buf) <= 1) continue;
        
        field f = parse_field(buf);
        if (f.type != -1) {  
            fields[field_count++] = f;
        }
    }
    
    fclose(in);

    for (int model = 0; model < 4; model++) {
        int min_size, max_size;
        bitmask_dp(model, &min_size, &max_size);
        printf("%d %d\n", min_size, max_size);
    }

    return 0;
}