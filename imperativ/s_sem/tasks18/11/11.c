#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

typedef enum { J_OBJECT, J_ARRAY, J_STRING, J_NUMBER, J_BOOL, J_NULL } NodeType;

typedef struct Node {
    NodeType type;
    char *key;
    union {
        char *s_val;
        double d_val;
        int b_val;
    };
    struct Node **children;
    int count;
} Node;

char *buffer;
int pos = 0;

void skip_stuff() {
    while (buffer[pos]) {
        if (isspace((unsigned char)buffer[pos])) {
            pos++;
        } else if (buffer[pos] == '/' && buffer[pos + 1] == '/') {
            while (buffer[pos] && buffer[pos] != '\n') pos++;
        } else if (buffer[pos] == '/' && buffer[pos + 1] == '*') {
            pos += 2;
            while (buffer[pos] && !(buffer[pos] == '*' && buffer[pos + 1] == '/')) pos++;
            if (buffer[pos]) pos += 2;
        } else {
            break;
        }
    }
}

char *parse_string_raw() {
    skip_stuff();
    if (buffer[pos] == '"') pos++;
    int start = pos;
    int capacity = 16;
    int size = 0;
    char *res = malloc(capacity);

    while (buffer[pos] && buffer[pos] != '"') {
        if (size + 1 >= capacity) {
            capacity *= 2;
            res = realloc(res, capacity);
        }
        if (buffer[pos] == '\\') {
            pos++;
            switch (buffer[pos]) {
                case 'n': res[size++] = '\n'; break;
                case 't': res[size++] = '\t'; break;
                case 'r': res[size++] = '\r'; break;
                case 'b': res[size++] = '\b'; break;
                case 'f': res[size++] = '\f'; break;
                case '"': res[size++] = '"'; break;
                case '\\': res[size++] = '\\'; break;
                case '/': res[size++] = '/'; break;
                case 'u': {
                    pos++;
                    unsigned int code;
                    sscanf(buffer + pos, "%4x", &code);
                    pos += 3;
                    if (code <= 0x7F) {
                        res[size++] = (char)code;
                    } else if (code <= 0x7FF) {
                        res = realloc(res, capacity += 2);
                        res[size++] = (char)(0xC0 | (code >> 6));
                        res[size++] = (char)(0x80 | (code & 0x3F));
                    } else {
                        res = realloc(res, capacity += 3);
                        res[size++] = (char)(0xE0 | (code >> 12));
                        res[size++] = (char)(0x80 | ((code >> 6) & 0x3F));
                        res[size++] = (char)(0x80 | (code & 0x3F));
                    }
                    break;
                }
            }
        } else {
            res[size++] = buffer[pos];
        }
        pos++;
    }
    if (buffer[pos] == '"') pos++;
    res[size] = '\0';
    return res;
}

Node *parse_value();

Node *parse_object() {
    Node *node = calloc(1, sizeof(Node));
    node->type = J_OBJECT;
    pos++;
    while (1) {
        skip_stuff();
        if (buffer[pos] == '}') { pos++; break; }
        char *key = parse_string_raw();
        skip_stuff();
        if (buffer[pos] == ':') pos++;
        Node *val = parse_value();
        val->key = key;
        node->children = realloc(node->children, sizeof(Node*) * (node->count + 1));
        node->children[node->count++] = val;
        skip_stuff();
        if (buffer[pos] == ',') pos++;
        else if (buffer[pos] == '}') { pos++; break; }
    }
    return node;
}

Node *parse_array() {
    Node *node = calloc(1, sizeof(Node));
    node->type = J_ARRAY;
    pos++;
    while (1) {
        skip_stuff();
        if (buffer[pos] == ']') { pos++; break; }
        Node *val = parse_value();
        char *idx_key = malloc(16);
        sprintf(idx_key, "%d", node->count);
        val->key = idx_key;
        node->children = realloc(node->children, sizeof(Node*) * (node->count + 1));
        node->children[node->count++] = val;
        skip_stuff();
        if (buffer[pos] == ',') pos++;
        else if (buffer[pos] == ']') { pos++; break; }
    }
    return node;
}

Node *parse_value() {
    skip_stuff();
    if (buffer[pos] == '{') return parse_object();
    if (buffer[pos] == '[') return parse_array();
    if (buffer[pos] == '"') {
        Node *n = calloc(1, sizeof(Node));
        n->type = J_STRING;
        n->s_val = parse_string_raw();
        return n;
    }
    Node *n = calloc(1, sizeof(Node));
    if (strncmp(buffer + pos, "true", 4) == 0) { n->type = J_BOOL; n->b_val = 1; pos += 4; }
    else if (strncmp(buffer + pos, "false", 5) == 0) { n->type = J_BOOL; n->b_val = 0; pos += 5; }
    else if (strncmp(buffer + pos, "null", 4) == 0) { n->type = J_NULL; pos += 4; }
    else {
        n->type = J_NUMBER;
        char *end;
        n->d_val = strtod(buffer + pos, &end);
        pos = end - buffer;
    }
    return n;
}

int32_t calculate_bson_size(Node *node) {
    int32_t size = 4 + 1;
    for (int i = 0; i < node->count; i++) {
        Node *child = node->children[i];
        size += 1 + strlen(child->key) + 1;
        if (child->type == J_NUMBER) size += 8;
        else if (child->type == J_STRING) size += 4 + strlen(child->s_val) + 1;
        else if (child->type == J_BOOL) size += 1;
        else if (child->type == J_OBJECT || child->type == J_ARRAY) size += calculate_bson_size(child);
    }
    return size;
}

void write_bson(FILE *out, Node *node) {
    if (node->type == J_OBJECT || node->type == J_ARRAY) {
        int32_t size = calculate_bson_size(node);
        fwrite(&size, 4, 1, out);
        for (int i = 0; i < node->count; i++) {
            Node *c = node->children[i];
            uint8_t t;
            switch (c->type) {
                case J_NUMBER: t = 0x01; break;
                case J_STRING: t = 0x02; break;
                case J_OBJECT: t = 0x03; break;
                case J_ARRAY:  t = 0x04; break;
                case J_BOOL:   t = 0x08; break;
                case J_NULL:   t = 0x0A; break;
            }
            fwrite(&t, 1, 1, out);
            fwrite(c->key, 1, strlen(c->key) + 1, out);
            if (c->type == J_NUMBER) fwrite(&c->d_val, 8, 1, out);
            else if (c->type == J_STRING) {
                int32_t l = strlen(c->s_val) + 1;
                fwrite(&l, 4, 1, out);
                fwrite(c->s_val, 1, l, out);
            } else if (c->type == J_BOOL) {
                uint8_t b = c->b_val;
                fwrite(&b, 1, 1, out);
            } else if (c->type == J_OBJECT || c->type == J_ARRAY) {
                write_bson(out, c);
            }
        }
        uint8_t zero = 0;
        fwrite(&zero, 1, 1, out);
    }
}

int main() {
    FILE *in = fopen("input.txt", "rb");
    fseek(in, 0, SEEK_END);
    long fsize = ftell(in);
    fseek(in, 0, SEEK_SET);
    buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, in);
    buffer[fsize] = 0;
    fclose(in);

    Node *root = parse_value();
    FILE *out = fopen("output.txt", "wb");
    write_bson(out, root);
    fclose(out);
    return 0;
}