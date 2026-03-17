#include "hashmap.h"
#include <stdlib.h>

#if defined(_WIN32)
#ifdef HASHMAP_EXPORTS
#define HM_API __declspec(dllexport)
#else
#define HM_API 
#endif /*HASHMAP_EXPORTS*/
#else
#define HM_API __attribute__((visibility("default")))
#endif /*defined(_WIN32)*/

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR_THRESHOLD 0.7

static const char TOMBSTONE;

static int find_slot(const HashMap *self, cpvoid key, int *found) {
    if (self->size == 0) {
        *found = 0;
        return -1;
    }

    uint32_t h = self->hash(self->context, key);
    uint32_t start = h % self->size;
    uint32_t i = start;
    int first_tombstone = -1;

    do {
        if (self->keys[i] == NULL) {
            if (first_tombstone != -1) {
                *found = 0;
                return first_tombstone;
            }
            *found = 0;
            return (int)i;
        } else if (self->keys[i] == &TOMBSTONE) {
            if (first_tombstone == -1) {
                first_tombstone = (int)i;
            }
        } else if (self->equal(self->context, self->keys[i], key)) {
            *found = 1;
            return (int)i;
        }
        i = (i + 1) % self->size;
    } while (i != start);

    *found = 0;
    return first_tombstone;
}

static void rehash(HashMap *self) {
    uint32_t old_size = self->size;
    cpvoid *old_keys = self->keys;
    cpvoid *old_values = self->values;

    self->size = (old_size == 0) ? INITIAL_CAPACITY : old_size * 2;
    self->keys = calloc(self->size, sizeof(cpvoid));
    self->values = calloc(self->size, sizeof(cpvoid));
    self->occupied = 0;

    for (uint32_t i = 0; i < old_size; i++) {
        if (old_keys[i] != NULL && old_keys[i] != &TOMBSTONE) {
            HM_Set(self, old_keys[i], old_values[i]);
        }
    }

    free(old_keys);
    free(old_values);
}

HM_API
HashMap HM_Init(EqualFunc ef, HashFunc hf, void *context) {
    HashMap map;
    map.size = 0;
    map.occupied = 0;
    map.equal = ef;
    map.hash = hf;
    map.context = context;
    map.keys = NULL;
    map.values = NULL;
    return map;
}

HM_API
void HM_Clear(HashMap *self) {
    free(self->keys);
    free(self->values);
    self->keys = NULL;
    self->values = NULL;
    self->size = 0;
    self->occupied = 0;
}

HM_API
cpvoid HM_Get(const HashMap *self, cpvoid key) {
    int found;
    int idx = find_slot(self, key, &found);
    if (found) {
        return self->values[idx];
    }
    return NULL;
}

HM_API
void HM_Set(HashMap *self, cpvoid key, cpvoid value) {
    if (self->size == 0 || (double)(self->occupied + 1) / self->size > LOAD_FACTOR_THRESHOLD) {
        rehash(self);
    }

    int found;
    int idx = find_slot(self, key, &found);

    if (found) {
        self->values[idx] = value;
    } else if (idx != -1) {
        self->keys[idx] = key;
        self->values[idx] = value;
        self->occupied++;
    }
}

HM_API
cpvoid HM_Remove(HashMap *self, cpvoid key) {
    int found;
    int idx = find_slot(self, key, &found);

    if (found) {
        cpvoid old_value = self->values[idx];
        self->keys[idx] = &TOMBSTONE;
        self->values[idx] = NULL;
        self->occupied--;
        return old_value;
    }
    return NULL;
}