#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char symbol0, symbol1, symbol2, symbol3, symbol4, symbol5, symbol6, symbol7, symbol8, symbol9;

void* sym_addrs[] = { &symbol0, &symbol1, &symbol2, &symbol3, &symbol4, &symbol5, &symbol6, &symbol7, &symbol8, &symbol9 };

typedef struct {
    int is_func;
    int is_ptr_to_var;
    int is_ptr_to_func;
    int ret_double;
    int arg_types[2];
    int arg_cnt;
} Symbol;

Symbol symbols[10];

double get_val(int id) {
    void* addr = sym_addrs[id];
    if (symbols[id].is_ptr_to_var) {
        addr = *(void**)addr;
    }
    if (symbols[id].ret_double) return *(double*)addr;
    return (double)(*(int*)addr);
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    int m;
    if (scanf("%d %d\n", &n, &m) != 2) return 0;

    for (int i = 0; i < n; i++) {
        char line[256];
        fgets(line, sizeof(line), stdin);

        if (strstr(line, "double") == line) symbols[i].ret_double = 1;
        
        if (strchr(line, '(')) {
            symbols[i].is_func = 1;
            if (strchr(line, '*')) symbols[i].is_ptr_to_func = 1;
            
            char *args_start = strrchr(line, '(') + 1;
            if (*args_start != ')') {
                symbols[i].arg_cnt = 1;
                symbols[i].arg_types[0] = (strstr(args_start, "double") != NULL);
                char *comma = strchr(args_start, ',');
                if (comma) {
                    symbols[i].arg_cnt = 2;
                    symbols[i].arg_types[1] = (strstr(comma, "double") != NULL);
                    
                    char first_arg[128];
                    int len = comma - args_start;
                    strncpy(first_arg, args_start, len);
                    first_arg[len] = '\0';
                    symbols[i].arg_types[0] = (strstr(first_arg, "double") != NULL);
                }
            }
        } else {
            if (strchr(line, '*')) symbols[i].is_ptr_to_var = 1;
        }
    }

    for (int i = 0; i < m; i++) {
        int s_idx, a1_idx, a2_idx;
        char req[256];
        fgets(req, sizeof(req), stdin);
        int cnt = sscanf(req, "%d %d %d", &s_idx, &a1_idx, &a2_idx);

        void* f_ptr = sym_addrs[s_idx];
        if (symbols[s_idx].is_ptr_to_func || symbols[s_idx].is_ptr_to_var) {
            f_ptr = *(void**)f_ptr;
        }

        if (!symbols[s_idx].is_func) {
            if (symbols[s_idx].ret_double) printf("%.15f\n", *(double*)f_ptr);
            else printf("%d\n", *(int*)f_ptr);
        } else {
            double v1 = (cnt >= 2) ? get_val(a1_idx) : 0;
            double v2 = (cnt >= 3) ? get_val(a2_idx) : 0;

            if (symbols[s_idx].arg_cnt == 0) {
                if (symbols[s_idx].ret_double) printf("%.15f\n", ((double (*)())f_ptr)());
                else printf("%d\n", ((int (*)())f_ptr)());
            } else if (symbols[s_idx].arg_cnt == 1) {
                if (symbols[s_idx].arg_types[0]) {
                    if (symbols[s_idx].ret_double) printf("%.15f\n", ((double (*)(double))f_ptr)(v1));
                    else printf("%d\n", ((int (*)(double))f_ptr)(v1));
                } else {
                    if (symbols[s_idx].ret_double) printf("%.15f\n", ((double (*)(int))f_ptr)((int)v1));
                    else printf("%d\n", ((int (*)(int))f_ptr)((int)v1));
                }
            } else {
                int t1 = symbols[s_idx].arg_types[0];
                int t2 = symbols[s_idx].arg_types[1];
                if (symbols[s_idx].ret_double) {
                    if (!t1 && !t2) printf("%.15f\n", ((double (*)(int, int))f_ptr)((int)v1, (int)v2));
                    else if (!t1 && t2) printf("%.15f\n", ((double (*)(int, double))f_ptr)((int)v1, v2));
                    else if (t1 && !t2) printf("%.15f\n", ((double (*)(double, int))f_ptr)(v1, (int)v2));
                    else printf("%.15f\n", ((double (*)(double, double))f_ptr)(v1, v2));
                } else {
                    if (!t1 && !t2) printf("%d\n", ((int (*)(int, int))f_ptr)((int)v1, (int)v2));
                    else if (!t1 && t2) printf("%d\n", ((int (*)(int, double))f_ptr)((int)v1, v2));
                    else if (t1 && !t2) printf("%d\n", ((int (*)(double, int))f_ptr)(v1, (int)v2));
                    else printf("%d\n", ((int (*)(double, double))f_ptr)(v1, v2));
                }
            }
        }
    }
    return 0;
}