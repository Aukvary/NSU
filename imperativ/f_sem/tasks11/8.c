#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000000
#define MOD 1000000007
#define P 131

typedef long long ll;

typedef struct HashNode {
    ll hash;
    int color;
    struct HashNode* next;
} HashNode;

HashNode* hash_table[MAX_N];
int color_counter = 0;

int find_or_insert(ll hash) {
    int index = hash % MAX_N;
    if (index < 0) index += MAX_N;
    
    HashNode* node = hash_table[index];
    while (node != NULL) {
        if (node->hash == hash) {
            return node->color;
        }
        node = node->next;
    }
    
    HashNode* new_node = malloc(sizeof(HashNode));
    new_node->hash = hash;
    new_node->color = color_counter++;
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
    
    return new_node->color;
}

int main() {
    int N, B;
    scanf("%d %d", &N, &B);
    
    char S[MAX_N + 1];
    scanf("%s", S);
    
    ll* p_pow = malloc(N * sizeof(ll));
    p_pow[0] = 1;
    for (int i = 1; i < N; i++) {
        p_pow[i] = (p_pow[i-1] * P) % MOD;
    }
    
    ll* h = malloc((N + 1) * sizeof(ll));
    h[0] = 0;
    for (int i = 0; i < N; i++) {
        h[i+1] = (h[i] + (S[i] - 'a' + 1) * p_pow[i]) % MOD;
    }
    
    int* colors = malloc((N - B + 1) * sizeof(int));
    
    for (int i = 0; i <= N - B; i++) {
        ll cur_h = (h[i + B] - h[i] + MOD) % MOD;
        cur_h = (cur_h * p_pow[N - 1 - i]) % MOD;
        
        colors[i] = find_or_insert(cur_h);
    }
    
    for (int i = 0; i <= N - B; i++) {
        if (i > 0) printf(" ");
        printf("%d", colors[i]);
    }
    printf("\n");
        
    return 0;
}