#include <stdio.h>

int calcLetters(char *iStr, int *oLowerCnt, int *oUpperCnt, int *oDigitsCnt) {
    int i = 0;
    for (; iStr[i] != '\0'; i++) {
        if (iStr[i] <= '9' && iStr[i] >= 0) *oDigitsCnt += 1;
        else if (iStr[i] <= 'Z' && iStr[i] >= 'A') *oUpperCnt += 1;
        else if (iStr[i] <= 'z' && iStr[i] >= 'a') *oLowerCnt += 1;
    }

    return i;
}

int main() {
    char s[127];
    FILE* in = fopen("input.txt", "r");
    int c = 0;
    int l = 0;
    int h = 0;
    int d = 0;
    int i = 0;
    for (int c = l = h = d = i = 0; fscanf(in, "%s\n", s) != -1; i++, c = l = h = d = 0) {
        c = calcLetters(s, &l, &h, &d);
        printf("Line %d has %d chars: %d are letters (%d lower, %d upper), %d are digits.\n", i, c, l + h, l, h, d);
    }

    return 0;
}