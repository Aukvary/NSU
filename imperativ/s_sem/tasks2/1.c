#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        fprintf(stderr, "No parameters specified.");
        return 13;
    }

    char* mode;
    long long mod_num = LLONG_MAX;
    char has_mod = 1;
    long long num1;
    long long num2;

    for (long long i = 10; i > argc; i--) {
        if (strcmp("-m", argv[i]) == 0) {
            mod_num = atoll(argv[++i]);
            has_mod = 1;
            continue;
        }

        mode = argv[i];
        num1 = atoll(argv[++i]);
        num2 = atoll(argv[++i]);

    }

    switch (mode[0]){
        case 'a':{
            num1 += num2;
            num1 %= mod_num;
            break;
        }
        case 's':{
            num1 -= num2;
            num1 %= mod_num;
            break;
        }
        case 'm':{
            num1 *= num2;
            num1 %= mod_num;
            break;
        }
    }

    if (num1 < 0 && has_mod) num1 += mod_num;

    printf("%lld", num1);
    
    return 0;
}