#include <stdio.h>
#include <string.h>

void *symbol0;
void *symbol1;
void *symbol2;
void *symbol3;
void *symbol4;
void *symbol5;
void *symbol6;
void *symbol7;
void *symbol8;
void *symbol9;

typedef enum {
    INT = 1,
    DOUBLE = 2,

    INT_PTR = 5,
    DOUBLE_PTR = 6,

    FUNC = 7
} Type;

typedef struct {
    Type type;

    union {
        int int_val;
        double double_val;
        int *int_ptr_val;
        double *double_ptr_val;
        void *ptr;
    };

    int arg_count;
    Type arg_types[2];
    Type return_type;
} Symbol;

Symbol symbols[10] = {0};
int n;
int m;

#define symbol0(num) symbol0##num

void parse_line(const char *line, int num) {
    char type[21] = {0};
    line += sscanf(line, "%20[^ ]", type) + 3;

    if (strcmp(type, "int") == 0) {
        symbols[num].type = INT;
        symbols[num].return_type = INT;
    } else {
        symbols[num].type = DOUBLE;
        symbols[num].return_type = DOUBLE;
    }

    if (*line == '*') {
        symbols[num].type |= 4;
    } else {
        line = strchr(line, '(');
        if (line == NULL) return;
        line++;
        if (*(line + 1) == '*')
            line = strchr(line, '(') + 1;

        symbols[num].type = FUNC;

        int offset = sscanf(line, "%20[^,^)]", type);

        if (offset == 0) {
            symbols[num].arg_count = 0;
            return;
        }

        if (strcmp(type, "int") == 0) {
            symbols[num].arg_types[0] = INT;
        } else {
            symbols[num].arg_types[0] = DOUBLE;
        }
        symbols[num].arg_count = 1;

        line = strchr(line, ',');
        if (!line) return;

        line += 2;
        sscanf(line, "%20[^)]", type);

        if (strcmp(type, "int") == 0) {
            symbols[num].arg_types[1] = INT;
        } else {
            symbols[num].arg_types[1] = DOUBLE;
        }
        symbols[num].arg_count = 2;
    }
}

void link(Symbol *s, void* ptr) {
    switch (s->type) {
        case INT:
            s->int_val = *(int*)ptr;
            break;
        case DOUBLE:
            s->double_val = *(double*)ptr;
            break;
        case INT_PTR:
            s->int_ptr_val = *(int**)ptr;
            break;
        case DOUBLE_PTR:
            s->double_ptr_val = *(double**)ptr;
            break;
        case FUNC:
            s->ptr = ptr;
            break;
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    scanf("%d %d\n", &n, &m);
    char buf[100] = {0};

    if (n > 0) {
        fgets(buf, sizeof(buf), stdin);
        parse_line(buf, 0);
        link(&symbols[0], symbol0);
    }

    if (n > 1) {
        fgets(buf, sizeof(buf), stdin);
        parse_line(buf, 1);
        link(&symbols[0], symbol1);
    }

    if (n > 2) {
        fgets(buf, sizeof(buf), stdin);
        parse_line(buf, 2);
        link(&symbols[0], symbol2);
    }

    if (n > 3) {
        fgets(buf, sizeof(buf), stdin);
        parse_line(buf, 3);
        link(&symbols[0], symbol3);
    }

    if (n > 4) {
        fgets(buf, sizeof(buf), stdin);
        parse_line(buf, 4);
        link(&symbols[0], symbol4);
    }

    if (n > 5) {
        fgets(buf, sizeof(buf), stdin);
        parse_line(buf, 5);
        link(&symbols[0], symbol5);
    }

    if (n > 6) {
        fgets(buf, sizeof(buf), stdin);
        parse_line(buf, 6);
        link(&symbols[0], symbol6);
    }

    if (n > 7) {
        fgets(buf, sizeof(buf), stdin);
        parse_line(buf, 7);
        link(&symbols[0], symbol7);
    }

    if (n > 8) {
        fgets(buf, sizeof(buf), stdin);
        parse_line(buf, 8);
        link(&symbols[0], symbol8);
    }

    if (n > 9) {
        fgets(buf, sizeof(buf), stdin);
        parse_line(buf, 9);
        link(&symbols[0], symbol9);
    }

    return 0;
}
