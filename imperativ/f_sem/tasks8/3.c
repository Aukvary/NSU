#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SPACE = ' ',
} symbs;

#define DECLARE_KEY_WORDS\
        X(PUK, "#include <stdio.h>#include <stdlib.h>#include <memory.h>#include <ctype.h>#include <math.h>#include <string.h>")\
        X(YAZ, "freopen(\"input.txt\", \"r\", stdin);\nfreopen(\"output.txt\", \"w\", stdout);")\
        X(HIYA, "__auto_type")\
        X(R, "return")

typedef enum {
    #define X(kw, replace) KW_##kw,
    DECLARE_KEY_WORDS
    #undef X
} key_words;

const char* kw_strs[] = {
    #define X(kw, replace) #kw,
    DECLARE_KEY_WORDS
    #undef X
};

const char* kw_replace_strs[] = {
    #define X(kw, replace) [KW_##kw] = replace,
    DECLARE_KEY_WORDS
    #undef X
};

char* is_key_word(const char* str) {
    for (int i = KW_PUK; i <= KW_R; i++) {
        char* kw_str = kw_strs[i];
        int dif_count = 0;
        for (int j = 0; str[j] != '\0'; j++) {
            if (kw_str[j] != str[j]) 
                dif_count++;

            if (dif_count == 2) return NULL;
        }

        return kw_replace_strs[i];
    }
}

int main() {
    char word_buf[101];
    int len = 0;

    char* replace = NULL;

    FILE* in = fopen("input.txt", "r");

    for (int c = getc(in); c != EOF; c = getc(in)) {
        if (c == SPACE) {
            if (replace = is_key_word())
            puts(word_buf);
            for (int i = 0; i < len; i++) word_buf[i] = 0;
            len = 0;
            putc(c, in);
        }
    }

    return 0;
}