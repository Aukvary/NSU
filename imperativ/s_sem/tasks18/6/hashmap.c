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


static int find_slot(const HashMap *self, cpvoid key, int *found) {
    uint32_t h = self->hash(key);
    int start = h % self->size;
    int i = start;

    do {
        if (self->keys[i] == NULL) {
            *found = 0;
            return i;
        }
        if (self->equal(self->keys[i], key)) {
            *found = 1;
            return i;
        }
        i = (i + 1) % self->size;
    } while (i != start);

    *found = 0;
    return -1;
}

HM_API HashMap HM_Init(EqualFunc ef, HashFunc hf, int size) {
    HashMap map;
    map.size = size;
    map.occupied = 0;
    map.equal = ef;
    map.hash = hf;
    map.keys = calloc(size, sizeof(cpvoid));
    map.values = calloc(size, sizeof(cpvoid));
    return map;
}

HM_API void HM_Destroy(HashMap *self) {
    free(self->keys);
    free(self->values);
    self->keys = NULL;
    self->values = NULL;
    self->size = 0;
    self->occupied = 0;
}

HM_API cpvoid HM_Get(const HashMap *self, cpvoid key) {
    int found;
    int idx = find_slot(self, key, &found);
    if (found && idx >= 0) {
        return self->values[idx];
    }
    return NULL;
}

HM_API void HM_Set(HashMap *self, cpvoid key, cpvoid value) {
    int found;
    int idx = find_slot(self, key, &found);

    if (found) {
        self->values[idx] = value;
    } else {
        self->keys[idx] = key;
        self->values[idx] = value;
        self->occupied++;
    }
}