#include <stdio.h>
#include <string.h>

#define SIZE 500

int main() {
    char words[SIZE][SIZE];
    FILE* in = fopen("input.txt", "r");
    int count = 0;
    char buf[SIZE * SIZE];
    
    while (fgets(buf, sizeof(buf), in) != NULL) {        
        char* word = strtok(buf, " \0\n\t"); 
        while (word != NULL) {
            strcpy(words[count++], word);
            word = strtok(NULL, " \0\n\t");
        }
    }
    
    for (int i = count - 1; i > -1; i--) {
        int len = strlen(words[i]);
        int res = len;

        for (int j = 1; j <= len; j++) {
            char uniq = 1;
            for (int k = 0; k < count; k++) {
                if (i == k)
                    continue;

                if (!strncmp(words[i], words[k], j)) {
                    uniq = 0;
                    break;
                }
            }

            if (uniq) {
                res = j;
                break;
            }
        }

        printf("%.*s", res, words[i]);
        if (i != 0)
            printf("#");
    }

    return 0;
}