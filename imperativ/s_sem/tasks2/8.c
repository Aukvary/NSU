#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *in = fopen("input.txt", "r");

    char line[256] = {0};
    fgets(line, sizeof(line), in);

    size_t n = strlen(line);
    while (n && (line[n-1] == '\n' || line[n-1] == '\r')) line[--n] = '\0';

    int i = 0;
    while (line[i]) {
        while (line[i] == ' ') 
            i++;      

        if (!line[i]) 
            break;

        char arg[256];
        int k = 0;
        int quats = 0;

        while (line[i] && (quats || line[i] != ' ')) {
            if (line[i] == '\\') {
                int backslash_count = 0;

                while (line[i] == '\\') { 
                    backslash_count++; 
                    i++; 
                }

                if (line[i] == '"') {
                    int pairs = backslash_count / 2;
                    while (pairs--) arg[k++] = '\\';

                    if (backslash_count % 2 == 0) {
                        quats = !quats;
                        i++; 
                    } else {
                        arg[k++] = '"';
                        i++; 
                    }
                } else {
                    while (backslash_count--) arg[k++] = '\\';
                }
            } else if (line[i] == '"') {
                if (quats && line[i+1] == '"') {
                    arg[k++] = '"';
                    i += 2;
                } else {
                    quats = !quats;
                    i++;
                }
            } else {
                arg[k++] = line[i++];
            }
        }

        arg[k] = '\0';
        printf("[%s]\n", arg);

        while (line[i] == ' ') i++;
    }
    return 0;
}