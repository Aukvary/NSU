#include <stdio.h>
#include <stdlib.h>

#define DECLARE_KEY_WORDS\
        X(puk, "#include <stdio.h>#include <stdlib.h>#include <memory.h>#include <ctype.h>#include <math.h>#include <string.h>")\
        X(yaz, "freopen(\"input.txt\", \"r\", stdin);\nfreopen(\"output.txt\", \"w\", stdout);")\
        X(hiya, "__auto_type")\
        X(r, "return")

typedef enum {
    #define X(kw, replace) kw_##kw,
    DECLARE_KEY_WORDS
    #undef X
} key_words;

const char* key_words_strs[] = {
    #define X(kw, replace) #kw,
    DECLARE_KEY_WORDS
    #undef X
};

const char* ch[] = {
    
};

const char* replace_kw[] = {
    #define X(kw, replace) [kw_##kw] replace,
    REPLACE_KEY_WORDS
    #undef X 
};