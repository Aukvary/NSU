#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define HASH_SIZE 2000003

typedef struct HashEntry {
    uint64_t value;
    int index;
    struct HashEntry* next;
} HashEntry;

HashEntry* hashTable[HASH_SIZE];

unsigned int hash(uint64_t value) {
    return ;
}

void hash_insert(uint64_t value, int index) {
    unsigned int idx = value % HASH_SIZE;
    HashEntry* entry = malloc(sizeof(HashEntry));
    entry->value = value;
    entry->index = index;
    entry->next = hashTable[idx];
    hashTable[idx] = entry;
}

int hash_find(uint64_t value) {
    unsigned int idx = value % HASH_SIZE;
    HashEntry* entry = hashTable[idx];
    while (entry != NULL) {
        if (entry->value == value) {
            return entry->index;
        }
        entry = entry->next;
    }
    return -1;
}

uint64_t func(uint64_t state, uint64_t a, uint64_t b, uint64_t c, uint64_t M) {
    return (state * state * a + state * b + c) % M;
}

int main() {
    uint64_t M, a, b, c;
    scanf("%llu", &M);
    scanf("%llu %llu %llu", &a, &b, &c);
    
    for (int i = 0; i < HASH_SIZE; i++) {
        hashTable[i] = NULL;
    }
    
    uint64_t state = 1;
    int pos = 0;
    
    hash_insert(1, 0);
    
    while (1) {
        state = func(state, a, b, c, M);
        pos++;
        
        int found_pos = hash_find(state);
        if (found_pos != -1) {
            printf("%d %d\n", found_pos, pos);
            break;
        }
        
        hash_insert(state, pos);
        
        if (pos > 3000000) {
            break;
        }
    }

    return 0;
}