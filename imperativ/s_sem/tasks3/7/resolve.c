#include <windows.h>
#include <stdint.h>

#define MAX 300001
void* checked[MAX];
int count = 0;

__declspec(dllexport)
void* resolve(void* address) {
    for (int i = 0; i < count; i++) {
        if (checked[i] == address) {
            return NULL; 
        }
    }
    
    if (count < MAX) {
        checked[count++] = address;
    }
    
    uint8_t* addr = (uint8_t*)address;
    uint8_t op1 = addr[0];
    uint8_t op2 = addr[1];
    
    if (op1 == 0xE9) {
        int32_t offset = *(int32_t*)(addr + 1);
        void* destAddr = (void*)((uint8_t*)address + 5 + offset);
        return resolve(destAddr);  
    }
    
    if (op1 == 0xFF && op2 == 0x25) {
        uint32_t* ptr = (uint32_t*)(addr + 2);
        void* destAddr = (void*)*ptr;
        return resolve(destAddr);  
    }
    
    return address;
}