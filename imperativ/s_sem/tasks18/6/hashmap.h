#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdint.h>

typedef const void *cpvoid;

typedef int (*EqualFunc)(cpvoid a, cpvoid b);
typedef uint32_t (*HashFunc)(cpvoid key);

typedef struct HashMap {
    cpvoid *keys;
    cpvoid *values;
    int size;
    int occupied;
    EqualFunc equal;
    HashFunc hash;
} HashMap;

HashMap HM_Init(EqualFunc ef, HashFunc hf, int size);
void HM_Destroy(HashMap *self);
cpvoid HM_Get(const HashMap *self, cpvoid key);
void HM_Set(HashMap *self, cpvoid key, cpvoid value);

#endif