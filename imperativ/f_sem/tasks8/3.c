#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Проверка, совпадает ли слово с учетом одной ошибки
int is_similar(const char *word, const char *target) {
    int len_word = strlen(word);
    int len_target = strlen(target);
    
    // Если длины отличаются больше чем на 1 - не может быть одной ошибки
    if (abs(len_word - len_target) > 1) {
        return 0;
    }
    
    // Проверка на точное совпадение
    if (strcmp(word, target) == 0) {
        return 1;
    }
    
    // Проверка на одну ошибку (замена символа)
    if (len_word == len_target) {
        int errors = 0;
        for (int i = 0; i < len_word; i++) {
            if (word[i] != target[i]) {
                errors++;
                if (errors > 1) return 0;
            }
        }
        return errors == 1;
    }
    
    // Проверка на пропуск/вставку одного символа
    if (len_word == len_target + 1) {
        // word длиннее на 1 (возможно, вставлен лишний символ)
        int i = 0, j = 0, errors = 0;
        while (i < len_word && j < len_target) {
            if (word[i] != target[j]) {
                errors++;
                i++;
                if (errors > 1) return 0;
            } else {
                i++;
                j++;
            }
        }
        return 1;
    }
    
    if (len_word + 1 == len_target) {
        // word короче на 1 (возможно, пропущен символ)
        int i = 0, j = 0, errors = 0;
        while (i < len_word && j < len_target) {
            if (word[i] != target[j]) {
                errors++;
                j++;
                if (errors > 1) return 0;
            } else {
                i++;
                j++;
            }
        }
        return 1;
    }
    
    return 0;
}

// Функция для обработки слова
void process_word(const char *word, FILE *out) {
    if (is_similar(word, "puk")) {
        fprintf(out, "#include <stdio.h>\n");
        fprintf(out, "#include <stdlib.h>\n");
        fprintf(out, "#include <memory.h>\n");
        fprintf(out, "#include <ctype.h>\n");
        fprintf(out, "#include <math.h>\n");
        fprintf(out, "#include <string.h>\n");
    } else if (is_similar(word, "hiya")) {
        fprintf(out, "__auto_type");
    } else if (is_similar(word, "yaz")) {
        fprintf(out, "freopen(\"input.txt\", \"r\", stdin);\n");
        fprintf(out, "freopen(\"output.txt\", \"w\", stdout);");
    } else {
        fprintf(out, "%s", word);
    }
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    if (!in || !out) {
        printf("Error opening files\n");
        return 1;
    }
    
    char ch;
    char word[100];
    int word_index = 0;
    int in_word = 0;
    
    while ((ch = fgetc(in)) != EOF) {
        if (isalnum(ch) || ch == '_') {
            // Мы внутри слова
            if (!in_word) {
                in_word = 1;
                word_index = 0;
            }
            if (word_index < 99) {
                word[word_index++] = ch;
            }
        } else {
            // Мы вне слова
            if (in_word) {
                word[word_index] = '\0';
                process_word(word, out);
                in_word = 0;
            }
            fputc(ch, out);
        }
    }
    
    // Обработка последнего слова, если файл заканчивается словом
    if (in_word) {
        word[word_index] = '\0';
        process_word(word, out);
    }
    
    fclose(in);
    fclose(out);
    return 0;
}