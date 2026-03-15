#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <json-c/json.h>

void write_value(FILE *out, struct json_object *obj);

int32_t calculate_size(struct json_object *obj) {
    int32_t size = 4 + 1; 
    
    if (json_object_get_type(obj) == json_type_object) {
        json_object_object_foreach(obj, key, val) {
            size += 1; 
            size += strlen(key) + 1; 
            
            enum json_type type = json_object_get_type(val);
            if (type == json_type_int || type == json_type_double) size += 8;
            else if (type == json_type_string) size += 4 + strlen(json_object_get_string(val)) + 1;
            else if (type == json_type_boolean) size += 1;
            else if (type == json_type_null) size += 0;
            else if (type == json_type_object || type == json_type_array) size += calculate_size(val);
        }
    } else if (json_object_get_type(obj) == json_type_array) {
        int len = json_object_array_length(obj);
        for (int i = 0; i < len; i++) {
            struct json_object *val = json_object_array_get_idx(obj, i);
            char key[32];
            sprintf(key, "%d", i);
            size += 1;
            size += strlen(key) + 1;

            enum json_type type = json_object_get_type(val);
            if (type == json_type_int || type == json_type_double) size += 8;
            else if (type == json_type_string) size += 4 + strlen(json_object_get_string(val)) + 1;
            else if (type == json_type_boolean) size += 1;
            else if (type == json_type_null) size += 0;
            else if (type == json_type_object || type == json_type_array) size += calculate_size(val);
        }
    }
    return size;
}

void write_element(FILE *out, const char *key, struct json_object *val) {
    enum json_type type = json_object_get_type(val);
    uint8_t bson_type;

    switch (type) {
        case json_type_double:
        case json_type_int:     bson_type = 0x01; break;
        case json_type_string:  bson_type = 0x02; break;
        case json_type_object:  bson_type = 0x03; break;
        case json_type_array:   bson_type = 0x04; break;
        case json_type_boolean: bson_type = 0x08; break;
        case json_type_null:    bson_type = 0x0A; break;
        default: return;
    }

    fwrite(&bson_type, 1, 1, out);
    fwrite(key, 1, strlen(key) + 1, out);
    write_value(out, val);
}

void write_value(FILE *out, struct json_object *obj) {
    enum json_type type = json_object_get_type(obj);

    if (type == json_type_int || type == json_type_double) {
        double d = json_object_get_double(obj);
        fwrite(&d, 8, 1, out);
    } else if (type == json_type_string) {
        const char *s = json_object_get_string(obj);
        int32_t len = strlen(s) + 1;
        fwrite(&len, 4, 1, out);
        fwrite(s, 1, len, out);
    } else if (type == json_type_boolean) {
        uint8_t b = json_object_get_boolean(obj) ? 1 : 0;
        fwrite(&b, 1, 1, out);
    } else if (type == json_type_null) {
    } else if (type == json_type_object) {
        int32_t size = calculate_size(obj);
        fwrite(&size, 4, 1, out);
        json_object_object_foreach(obj, key, val) {
            write_element(out, key, val);
        }
        uint8_t zero = 0;
        fwrite(&zero, 1, 1, out);
    } else if (type == json_type_array) {
        int32_t size = calculate_size(obj);
        fwrite(&size, 4, 1, out);
        int len = json_object_array_length(obj);
        for (int i = 0; i < len; i++) {
            char key[32];
            sprintf(key, "%d", i);
            write_element(out, key, json_object_array_get_idx(obj, i));
        }
        uint8_t zero = 0;
        fwrite(&zero, 1, 1, out);
    }
}

int main() {
    FILE *in = fopen("input.txt", "rb");
    if (!in) return 1;

    fseek(in, 0, SEEK_END);
    long fsize = ftell(in);
    fseek(in, 0, SEEK_SET);

    char *data = malloc(fsize + 1);
    fread(data, 1, fsize, in);
    data[fsize] = 0;
    fclose(in);

    struct json_object *root = json_tokener_parse(data);
    free(data);

    FILE *out = fopen("output.txt", "wb");
    if (root && out) {
        write_value(out, root);
        json_object_put(root);
    }
    if (out) fclose(out);

    return 0;
}