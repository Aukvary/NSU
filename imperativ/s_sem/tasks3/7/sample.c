#include <stdio.h>
#include <stdint.h>
#include <assert.h>

void* resolve(void *address);   //note: link against import library to get it resolved!

char memory[1024] = {
    0xE9, 0x05, 0x00, 0x00, 0x00, 0xCC, 0x15, 0x00, 0x00, 0x00, 0xFF, 0x25, 0x06, 0x00, 0x00, 0x00,
    0xE9, 0xEB, 0xFF, 0xFF, 0xFF, 0x20, 0xCC, 0xCC, 0xCC, 0xCC, 0xE9, 0xF1, 0xFF, 0xFF, 0xFF, 0xCC
};

int main() {

    
    assert(sizeof(void*) == 4);
    #define FIXADDR(offset) *(uint32_t*)(&memory[offset]) += (uint32_t)memory;
    FIXADDR(0x06)
    FIXADDR(0x0C)
    //set breakpoint here, and inspect "memory,x" in MSVC watch
    assert(resolve(memory + 0x15) == memory + 0x15);
    assert(resolve(memory + 0x0A) == memory + 0x15);
    assert(resolve(memory + 0x00) == memory + 0x15);
    assert(resolve(memory + 0x10) == memory + 0x15);
    assert(resolve(memory + 0x1A) == memory + 0x15);
    assert(resolve(memory + 0x11) == memory + 0x11);
    memory[0x15] = 0xE9;
    *(uint32_t*)(&memory[0x16]) = 0x00000000;
    assert(resolve(memory + 0x15) == 0);
    assert(resolve(memory + 0x00) == 0);
    memory[0x1B]++;
    assert(resolve(memory + 0x00) == memory + 0x11);

#if 0   //note: change to 1 to have some fun =)
    DoFun();
#endif
    return 0;
}


#ifdef _WIN32       //for fun only =)
//note: including <windows.h> would be the right way!
void* __stdcall GetProcAddress(void*, char*);
void* __stdcall LoadLibraryA(char*);
//note: forces linking a .lib file
#pragma comment(lib, "kernel32.lib")

int DoFun() {
    //set breakpoint here, open Debug->Windows->Disassembly and use "Step Into" to see how it goes
    GetProcAddress(NULL, NULL);         
    //see if our resolver finds correct location:
    void *address = resolve(GetProcAddress);
    void *addressReal = GetProcAddress(LoadLibraryA("kernel32.dll"), "GetProcAddress");
    assert(address == addressReal);
}
#endif
