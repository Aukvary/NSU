#include <windows.h>
#include <stdint.h>

static void* step(void *address) {
    uint8_t b0 = *(uint8_t*)address;

    if (b0 == 0xE9) {
        int rel = *(int32_t*)((uint8_t*)address + 1);
        return (uint8_t*)address + 5 + rel;
    }

    if (b0 == 0xFF && *((uint8_t*)address + 1) == 0x25) {
        uint32_t ptr = *((uint32_t*)((uint8_t*)address + 2));
        return *(void**)(uint8_t*)ptr;
    }

    return address;
}

__declspec(dllexport) 
void* resolve(void* address) {
    void* n1 = step(address);
    if (n1 == address) return address;

    void* slow = address;
    void* fast = address;

    while (1) {
        slow = step(slow);
        if (slow == step(slow)) return slow;

        fast = step(fast);
        if (fast == step(fast)) return fast;
        fast = step(fast);
        if (fast == step(fast)) return fast;

        if (slow == fast) return NULL;
    }
}