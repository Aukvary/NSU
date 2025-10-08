#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* concat(char* pref, char* suff) {
    int pn = strlen(pref);
    int sn =  strlen(suff);

    char* new = malloc(pn + sn + 1);

    int len = 0;

    for (int i = 0; i < pn; i++)
        new[len++] = pref[i];


    for (int i = 0; i < sn; i++)
        new[len++] = suff[i];

    new[pn + sn] = '\0';
    


    return new;
}


int main() {
    int n;
    FILE* in = fopen("input.txt", "r");
    fscanf(in, "%d\n", &n);
    char* res = "";

    for (int i = 0; i < n; i++) {
        char s[100];
        fscanf(in, "%s\n", s);
        if (i == 0)
            res = concat(res, s);
        else if (i == 1)
            res = concat(res, s);
        else 
            res = concat(res, s);
    }

    printf("%s", res);


    return 0;
}
