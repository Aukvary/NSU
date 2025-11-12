#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DECLARE_KEY_WORDS\
    X(puk, "#include <stdio.h>\n#include <stdlib.h>\n#include <memory.h>\n#include <ctype.h>\n#include <math.h>\n#include <string.h>")\
    X(yaz, "freopen(\"input.txt\", \"r\", stdin);\n    freopen(\"output.txt\", \"w\", stdout);")\
    X(hiya, "__auto_type")

typedef enum {
    #define X(kw, replace) kw,
    DECLARE_KEY_WORDS
    #undef X
    NOT_KEYWORD
} key_words;

const char* kw_keys[] = {
    #define X(kw, replace) #kw,
    DECLARE_KEY_WORDS
    #undef X
};

const char* kw_replaces[] = {
    #define X(kw, replace) replace,
    DECLARE_KEY_WORDS
    #undef X
};

int is_key_word(const char* word) {
    for (int i = 0; i <= hiya; i++) {
        int len1 = strlen(word);
        int len2 = strlen(kw_keys[i]);
        
        if (len1 < len2 - 1 || len1 > len2 + 1) {
            continue;
        }
        
        int dif_count = 0;
        int j = 0, k = 0;
        
        while (j < len1 && k < len2) {
            if (word[j] != kw_keys[i][k]) {
                dif_count++;
                if (dif_count > 1) break;
                
                if (len1 > len2) j++;
                else if (len2 > len1) k++;
                else { j++; k++; }
            } else {
                j++;
                k++;
            }
        }
        
        dif_count += (len1 - j) + (len2 - k);
        
        if (dif_count <= 1) {
            return i;
        }
    }
    return -1;
}

int main() {
    FILE* in = fopen("input.txt", "r");

    int c;
    char buf[100] = {0};
    int buf_ptr = 0;

    while ((c = fgetc(in)) != EOF) {
        if (isalpha(c)) {
            buf[buf_ptr++] = c;
        } else {
            if (buf_ptr) {
                buf[buf_ptr] = '\0';
                int kw_index = is_key_word(buf);
                if (kw_index != -1) {
                    printf("%s", kw_replaces[kw_index]);
                } else {
                    printf("%s", buf);
                }
                buf_ptr = 0;
            }
            
            printf("%c", c);
        }
    }

    if (buf_ptr) {
        buf[buf_ptr] = '\0';
        int kw_index = is_key_word(buf);
        if (kw_index != -1) {
            printf("%s", kw_replaces[kw_index]);
        } else {
            printf("%s", buf);
        }
    }

    return 0;
}