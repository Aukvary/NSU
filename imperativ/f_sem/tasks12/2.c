#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    double value;
    struct Block* next;
} Block;

typedef struct MyDoubleHeap_s {
    Block* memory;
    Block* free_list_head;
    int count;
} MyDoubleHeap;

MyDoubleHeap initAllocator(int slotsCount) {
    MyDoubleHeap heap;
    heap.count = slotsCount;
    heap.memory = (Block*)malloc(slotsCount * sizeof(Block));
    heap.free_list_head = heap.memory;
    
    for (int i = 0; i < slotsCount - 1; i++) {
        heap.memory[i].next = &heap.memory[i + 1];
    }
    heap.memory[slotsCount - 1].next = NULL;
    
    return heap;
}

double* allocDouble(MyDoubleHeap* heap) {
    if (heap->free_list_head == NULL) {
        return NULL;
    }
    
    Block* block = heap->free_list_head;
    heap->free_list_head = block->next;
    block->next = NULL;
    return &(block->value);
}

void freeDouble(MyDoubleHeap* heap, double* ptr) {
    Block* block = (Block*)((char*)ptr - ((char*)&((Block*)0)->value));
    block->next = heap->free_list_head;
    heap->free_list_head = block;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n;
    int q;
    scanf("%d %d", &n, &q);
    
    MyDoubleHeap heap = initAllocator(n);
    double* operations[300005];

    for (int i = 0; i < q; i++) {
        int t;
        scanf("%d", &t);
        
        if (t == 0) {
            double value;
            scanf("%lf", &value);
            
            double* ptr = allocDouble(&heap);
            operations[i] = ptr;
            
            if (ptr == NULL) {
                printf("00000000\n");
            } else {
                printf("%p\n", (void*)ptr);
                *ptr = value;
            }
        }
        else if (t == 1) {
            int k;
            scanf("%d", &k);
            
            double* ptr = operations[k];
            if (ptr != NULL) {
                freeDouble(&heap, ptr);
            }
        }
        else if (t == 2) {
            int k;
            scanf("%d", &k);
            
            double* ptr = operations[k];
            printf("%0.5lf\n", *ptr);
        }
    }
    
    free(heap.memory);
    
    return 0;
}