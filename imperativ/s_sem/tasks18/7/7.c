#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Value Value;

typedef struct ObjectField {
    char* key;
    Value* value;
    struct ObjectField* next;
} ObjectField;

typedef struct Array {
    Value** items;
    int count;
    int capacity;
} Array;

struct Value {
    int type;
    union {
        char* string;
        Array* array;
        ObjectField* object;
        int number;
        int boolean;
        int null;
    } data;
};

enum {
    TYPE_OBJECT,
    TYPE_ARRAY,
    TYPE_STRING,
    TYPE_NUMBER,
    TYPE_BOOLEAN,
    TYPE_NULL
};

char* input;
int pos;
int input_len;

char* read_string() {
    pos++;
    int start = pos;
    while (input[pos] != '"') {
        pos++;
    }
    int len = pos - start;
    char* str = malloc(len + 1);
    memcpy(str, input + start, len);
    str[len] = '\0';
    pos++;
    return str;
}

void skip_whitespace() {
    while (pos < input_len && isspace(input[pos])) {
        pos++;
    }
}

Value* parse_value();

Value* parse_object() {
    pos++;
    skip_whitespace();
    ObjectField* head = NULL;
    ObjectField* tail = NULL;

    if (input[pos] != '}') {
        while (1) {
            skip_whitespace();
            char* key = read_string();
            skip_whitespace();
            pos++;
            skip_whitespace();
            Value* val = parse_value();

            ObjectField* field = malloc(sizeof(ObjectField));
            field->key = key;
            field->value = val;
            field->next = NULL;

            if (!head) {
                head = field;
                tail = field;
            } else {
                tail->next = field;
                tail = field;
            }

            skip_whitespace();
            if (input[pos] == '}') break;
            pos++;
            skip_whitespace();
        }
    }
    pos++;

    Value* obj_val = malloc(sizeof(Value));
    obj_val->type = TYPE_OBJECT;
    obj_val->data.object = head;

    return obj_val;
}

Value* parse_array() {
    pos++;
    skip_whitespace();
    Array* arr = malloc(sizeof(Array));
    arr->count = 0;
    arr->capacity = 4;
    arr->items = malloc(sizeof(Value*) * arr->capacity);

    if (input[pos] != ']') {
        while (1) {
            skip_whitespace();
            Value* val = parse_value();

            if (arr->count >= arr->capacity) {
                arr->capacity *= 2;
                arr->items = realloc(arr->items, sizeof(Value*) * arr->capacity);
            }
            arr->items[arr->count++] = val;

            skip_whitespace();
            if (input[pos] == ']') break;
            pos++;
            skip_whitespace();
        }
    }
    pos++;

    Value* arr_val = malloc(sizeof(Value));
    arr_val->type = TYPE_ARRAY;
    arr_val->data.array = arr;

    return arr_val;
}

Value* parse_value() {
    skip_whitespace();
    Value* val = malloc(sizeof(Value));

    if (input[pos] == '{') {
        free(val);
        return parse_object();
    } else if (input[pos] == '[') {
        free(val);
        return parse_array();
    } else if (input[pos] == '"') {
        val->type = TYPE_STRING;
        val->data.string = read_string();
    } else if (strncmp(input + pos, "true", 4) == 0) {
        val->type = TYPE_BOOLEAN;
        val->data.boolean = 1;
        pos += 4;
    } else if (strncmp(input + pos, "false", 5) == 0) {
        val->type = TYPE_BOOLEAN;
        val->data.boolean = 0;
        pos += 5;
    } else if (strncmp(input + pos, "null", 4) == 0) {
        val->type = TYPE_NULL;
        val->data.null = 0;
        pos += 4;
    } else {
        val->type = TYPE_NUMBER;
        int start = pos;
        if (input[pos] == '-') pos++;
        while (isdigit(input[pos])) pos++;
        int len = pos - start;
        char* num_str = malloc(len + 1);
        memcpy(num_str, input + start, len);
        num_str[len] = '\0';
        val->data.number = atoi(num_str);
        free(num_str);
    }

    return val;
}

Value* parse_json() {
    skip_whitespace();
    return parse_value();
}

Value* find_by_path(Value* root, int k, char** steps) {
    Value* current = root;

    for (int i = 0; i < k; i++) {
        char* step = steps[i];

        if (step[0] == '[') {
            int index = atoi(step + 1);
            if (current->type == TYPE_ARRAY) {
                current = current->data.array->items[index];
            }
        } else {
            if (current->type == TYPE_OBJECT) {
                ObjectField* field = current->data.object;
                while (field) {
                    if (strcmp(field->key, step) == 0) {
                        current = field->value;
                        break;
                    }
                    field = field->next;
                }
            }
        }
    }

    return current;
}

void print_value(Value* val) {
    if (val->type == TYPE_OBJECT) {
        printf("<object>\n");
    } else if (val->type == TYPE_ARRAY) {
        printf("<array>\n");
    } else if (val->type == TYPE_STRING) {
        printf("\"%s\"\n", val->data.string);
    } else if (val->type == TYPE_NUMBER) {
        printf("%d\n", val->data.number);
    } else if (val->type == TYPE_BOOLEAN) {
        printf(val->data.boolean ? "true\n" : "false\n");
    } else if (val->type == TYPE_NULL) {
        printf("null\n");
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    input = malloc(1048576);
    input_len = 0;

    int c;
    while ((c = getchar()) != EOF) {
        input[input_len++] = c;
    }
    input[input_len] = '\0';

    char separator[] = "<<<>>>";
    char* json_end = strstr(input, separator);
    int json_len = json_end - input;

    char* json_input = malloc(json_len + 1);
    memcpy(json_input, input, json_len);
    json_input[json_len] = '\0';

    pos = 0;
    input = json_input;
    input_len = json_len;
    Value* root = parse_json();

    char* queries_start = json_end + strlen(separator);
    char* query_pos = queries_start;

    while (1) {
        while (*query_pos == '\n' || *query_pos == '\r') query_pos++;

        int k;
        sscanf(query_pos, "%d", &k);
        if (k == -1) break;

        while (*query_pos != '\n' && *query_pos != '\r') query_pos++;
        while (*query_pos == '\n' || *query_pos == '\r') query_pos++;

        char** steps = malloc(sizeof(char*) * k);
        for (int i = 0; i < k; i++) {
            char* step_start = query_pos;
            while (*query_pos != '\n' && *query_pos != '\r') query_pos++;
            int step_len = query_pos - step_start;
            steps[i] = malloc(step_len + 1);
            memcpy(steps[i], step_start, step_len);
            steps[i][step_len] = '\0';
            while (*query_pos == '\n' || *query_pos == '\r') query_pos++;
        }

        Value* result = find_by_path(root, k, steps);
        print_value(result);

        for (int i = 0; i < k; i++) {
            free(steps[i]);
        }
        free(steps);
    }
    
    return 0;
}