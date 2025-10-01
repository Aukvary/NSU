#include <stdio.h>

void swap(char* f, char* s) {
    char temp = *f;
    *f = *s;
    *s = temp;
}

void insert_sort(char* word, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && word[j] < word[j - 1]; j--) {
            swap(&word[j], &word[j - 1]);
        }
    }
}

int main() {
    int n;
    char s[27] = { 0 };    
    FILE* in = fopen("input.txt", "r");
    fscanf(in, "%d\n", &n);
    for (int i = 0; i < n; i++) {
        fscanf(in, "%c ", &s[i]);
    }

    int i = n - 2;

    while (i >= 0 && s[i] >= s[i + 1]) 
        i--;

    if (i < 0) {
        insert_sort(s, n);
        printf("%s", s);
        return 0;
    }

    int j = n - 1;
    while (j > i && s[j] <= s[i])
        j--;
    
    swap(&s[i], &s[j]);

    i++;
    j = n - 1;

    while (i < j) {
        swap(&s[i], &s[j]);
        i++;
        j--;
    }


    for (int i = 0; i < n; i++)
        printf("%c ", s[i]);

    return 0;
}