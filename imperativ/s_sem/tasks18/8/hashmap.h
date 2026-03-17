#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdint.h>

typedef const void *cpvoid;

typedef int (*EqualFunc)(void *context, cpvoid a, cpvoid b);
typedef uint32_t (*HashFunc)(void *context, cpvoid key);

typedef struct HashMap {
    cpvoid *keys;
    cpvoid *values;
    uint32_t size;
    uint32_t occupied;
    EqualFunc equal;
    HashFunc hash;
    void *context;
} HashMap;

HashMap HM_Init(EqualFunc ef, HashFunc hf, void *context);
void HM_Clear(HashMap *self);
cpvoid HM_Get(const HashMap *self, cpvoid key);
void HM_Set(HashMap *self, cpvoid key, cpvoid value);
cpvoid HM_Remove(HashMap *self, cpvoid key);

#endif