#include <stdio.h>
#include <string.h>

int main(void) {
    char words[200][1000];
    char pref[200][1000];
    int n = 0;
    char line[1000];
    while (fgets(line, 1000, stdin)) {
        int l = strlen(line);
        if (l && line[l-1] == '\n') 
            line[--l] = '\0';
        if (l && line[l-1] == '\r') 
            line[--l] = '\0';
        if (l == 0) 
            break;

        for (char *p = strtok(line, " "); p; p = strtok(NULL, " ")) {
            strncpy(words[n], p, 1000);
            words[n][999] = '\0';
            n++;
        }
    }

    for (int i = 0; i < n; i++) {
        int l = strlen(words[i]);
        int k = 1;
        for (; k <= l; k++) {
            int uniq = 1;
            for (int j = 0; j < n; j++) if (j != i)
                if (!strncmp(words[i], words[j], k)) { 
                    uniq = 0; 
                    break; 
                }
            if (uniq) 
                break;
        }
        if (k > l) 
            strcpy(pref[i], words[i]);
        else {
            strncpy(pref[i], words[i], k);
            pref[i][k] = '\0';
        }
    }

    char out[1000000] = "";
    for (int i = n - 1; i >= 0; i--) {
        if (n - 1 != i) 
            strcat(out, "#");
        strcat(out, pref[i]);
    }
    puts(out);
    return 0;
}
