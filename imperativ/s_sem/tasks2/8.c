#include <stdio.h>

int main() {
    FILE *in = fopen("input.txt", "r");

    char s[105] = {0};
    fgets(s, sizeof(s), in);

    int i = 0;
    while (s[i]) {
        while (s[i] == ' ') 
            i++;      

        if (!s[i]) 
            break;

        char arg[105];
        int k = 0;
        int quats = 0;

        while (s[i] && (quats || s[i] != ' ')) {
            if (s[i] == '\\') {
                int backslash_count = 0;

                while (s[i] == '\\') { 
                    backslash_count++; 
                    i++; 
                }

                if (s[i] == '"') {
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
            } else if (s[i] == '"') {
                if (quats && s[i+1] == '"') {
                    arg[k++] = '"';
                    i += 2;
                } else {
                    quats = !quats;
                    i++;
                }
            } else {
                arg[k++] = s[i++];
            }
        }

        arg[k] = '\0';
        printf("[%s]\n", arg);

        while (s[i] == ' ') i++;
    }
    return 0;
}