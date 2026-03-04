#include <stdio.h>

int main() {
    #if defined(_MSC_VER)
        printf("Compiler: MSVC\n");
    #elif defined(__clang__)
        printf("Compiler: clang\n");
    #elif defined(__GNUC__) && !defined(__TINYC__)
        printf("Compiler: GCC\n");
    #elif defined(__TINYC__)
        printf("Compiler: TCC\n");
    #else
        printf("Compiler: unknown\n");
    #endif

    #if defined(__x86_64__) || defined(_WIN64) || defined(__LP64__)
        printf("Bitness: 64\n");
    #else
        printf("Bitness: 32\n");
    #endif

    #ifdef NDEBUG
        printf("Assets: disabled\n");
    #else
        printf("Assets: enabled\n");
    #endif

    return 0;
}