#include <stdio.h>
#include <stdlib.h>

typedef struct MyDoubleHeap_s {
    char* memory;
    void** free_list_head;
    int slots_count;
} MyDoubleHeap;

MyDoubleHeap initAllocator(int slotsCount) {
    MyDoubleHeap heap;
    heap.slots_count = slotsCount;
    heap.memory = (char*)malloc(slotsCount * 8);
    heap.free_list_head = (void**)heap.memory;
    
    for (int i = 0; i < slotsCount - 1; i++) {
        void** current = (void**)(heap.memory + i * 8);
        *current = (void*)(heap.memory + (i + 1) * 8);
    }
    
    void** last = (void**)(heap.memory + (slotsCount - 1) * 8);
    *last = NULL;
    
    return heap;
}

double* allocDouble(MyDoubleHeap* heap) {
    if (heap->free_list_head == NULL) {
        return NULL;
    }
    
    void** block = heap->free_list_head;
    heap->free_list_head = (void**)(*block);
    return (double*)block;
}

void freeDouble(MyDoubleHeap* heap, double* ptr) {
    void** block = (void**)ptr;
    *block = (void*)heap->free_list_head;
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
                printf("%08llX\n", (unsigned long long)ptr);
            }
            
            if (ptr != NULL) {
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