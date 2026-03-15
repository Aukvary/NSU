#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum { J_OBJECT, J_ARRAY, J_VALUE } NodeType;

typedef struct Node {
    NodeType type;
    char *val;
    struct Entry *entries;
    int count;
} Node;

typedef struct Entry {
    char *key;
    Node *node;
} Entry;

char *buffer;
int pos = 0;

void skip_whitespace() {
    while (buffer[pos] && isspace((unsigned char) buffer[pos])) pos++;
}

char *parse_string() {
    skip_whitespace();
    if (buffer[pos] == '"') pos++;
    int start = pos;
    while (buffer[pos] && buffer[pos] != '"') pos++;
    int len = pos - start;
    char *res = malloc(len + 3);
    sprintf(res, "\"%.*s\"", len, buffer + start);
    if (buffer[pos] == '"') pos++;
    return res;
}

Node *parse_json();

Node *parse_object() {
    Node *node = calloc(1, sizeof(Node));
    node->type = J_OBJECT;
    pos++;
    while (1) {
        skip_whitespace();
        if (buffer[pos] == '}') {
            pos++;
            break;
        }
        char *key = parse_string();
        skip_whitespace();
        if (buffer[pos] == ':') pos++;
        Node *val = parse_json();
        node->entries = realloc(node->entries, sizeof(Entry) * (node->count + 1));
        node->entries[node->count].key = key;
        node->entries[node->count].node = val;
        node->count++;
        skip_whitespace();
        if (buffer[pos] == ',') pos++;
        else if (buffer[pos] == '}') {
            pos++;
            break;
        }
    }
    return node;
}

Node *parse_array() {
    Node *node = calloc(1, sizeof(Node));
    node->type = J_ARRAY;
    pos++;
    while (1) {
        skip_whitespace();
        if (buffer[pos] == ']') {
            pos++;
            break;
        }
        Node *val = parse_json();
        node->entries = realloc(node->entries, sizeof(Entry) * (node->count + 1));
        node->entries[node->count].key = NULL;
        node->entries[node->count].node = val;
        node->count++;
        skip_whitespace();
        if (buffer[pos] == ',') pos++;
        else if (buffer[pos] == ']') {
            pos++;
            break;
        }
    }
    return node;
}

Node *parse_simple_value() {
    skip_whitespace();
    int start = pos;
    while (buffer[pos] && !strchr(",}] \n\r\t", buffer[pos])) pos++;
    int len = pos - start;
    Node *node = calloc(1, sizeof(Node));
    node->type = J_VALUE;
    node->val = malloc(len + 1);
    memcpy(node->val, buffer + start, len);
    node->val[len] = '\0';
    return node;
}

Node *parse_json() {
    skip_whitespace();
    if (buffer[pos] == '{') return parse_object();
    if (buffer[pos] == '[') return parse_array();
    if (buffer[pos] == '"') {
        Node *node = calloc(1, sizeof(Node));
        node->type = J_VALUE;
        node->val = parse_string();
        return node;
    }
    return parse_simple_value();
}

void process_queries(Node *root, FILE *f_in, FILE *f_out) {
    int k;
    while (fscanf(f_in, "%d\n", &k) == 1 && k != -1) {
        Node *current = root;

        for (int i = 0; i < k; i++) {
            char key[100] = {0};
            fgets(key, sizeof(key), f_in);

            if (key[0] == '\"') {
                strrchr(key, '\"')[1] = '\0';
                for (int j = 0; j < current->count; j++) {
                    if (strcmp(current->entries[j].key, key) == 0) {
                        current = current->entries[j].node;
                        break;
                    }
                }
            } else {
                char str_idx[4] = {0};
                sscanf(key, "[%[^]]]", str_idx);
                int idx = atoi(str_idx);
                current = current->entries[idx].node;
            }
        }

        if (current->type == J_OBJECT) fprintf(f_out, "<object>\n");
        else if (current->type == J_ARRAY) fprintf(f_out, "<array>\n");
        else fprintf(f_out, "%s\n", current->val);
    }
}

int main() {
    FILE *f_in = fopen("input.txt", "r");

    buffer = malloc(1024 * 1024);
    int b_pos = 0;
    char line[2048];

    while (fgets(line, sizeof(line), f_in)) {
        if (strstr(line, "<<<>>>")) break;
        int len = strlen(line);
        memcpy(buffer + b_pos, line, len);
        b_pos += len;
    }
    buffer[b_pos] = '\0';

    Node *root = parse_json();

    FILE *f_out = fopen("output.txt", "w");

    process_queries(root, f_in, f_out);

    fclose(f_in);
    fclose(f_out);
    return 0;
}
