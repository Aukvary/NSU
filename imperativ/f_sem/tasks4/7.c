#include <stdio.h>
#include <string.h>

#define CHUNK_SIZE 1000

int main(void) {
    char words[CHUNK_SIZE][CHUNK_SIZE];
    char prefs[CHUNK_SIZE][CHUNK_SIZE];
    int n = 0;
    char line[CHUNK_SIZE];
    while (fgets(line, CHUNK_SIZE, fopen("input.txt", "r"))) {
        int l = strlen(line);
        if (l && (line[l-1] == '\n' || line[l-1] == '\r')) 
            line[--l] = '\0';
        if (l == 0) 
            break;

        for (char *p = strtok(line, " "); p; p = strtok(NULL, " ")) {
            strncpy(words[n], p, CHUNK_SIZE);
            words[n][CHUNK_SIZE - 1] = '\0';
            n++;
        }
    }

    for (int i = 0; i < n; i++) {
        int l = strlen(words[i]);
        int len = 1;
        for (; len <= l; len++) {
            int uniq = 1;
            for (int j = 0; j < n; j++) {
                if (j == i)
                    continue;
                if (!strncmp(words[i], words[j], len)) { 
                    uniq = 0; 
                    break; 
                }
            }
            if (uniq) 
                break;
        }
        if (len > l) 
            strcpy(prefs[i], words[i]);
        else {
            strncpy(prefs[i], words[i], len);
            prefs[i][len] = '\0';
        }
    }

    char res[CHUNK_SIZE] = "";
    for (int i = n - 1; i > -1; i--) {
        if (i != n - 1) 
            strcat(res, "#");
        strcat(res, prefs[i]);
    }
    puts(res);
    return 0;
}
