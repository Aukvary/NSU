#include <stdio.h>

int main() {
    #if defined(__clang__)
        printf("Compiler: clang\n");
    #elif defined(_MSC_VER)
        printf("Compiler: MSVC\n");
    #elif defined(__TINYC__)
        printf("Compiler: TCC\n");
    #elif defined(__GNUC__)
        printf("Compiler: GCC\n");
    #endif

    if (sizeof(void*) == 8) {
        printf("Bitness: 64\n");
    } else {
        printf("Bitness: 32\n");
    }

    #ifdef NDEBUG
        printf("Asserts: disabled\n");
    #else
        printf("Asserts: enabled\n");
    #endif

    return 0;
}