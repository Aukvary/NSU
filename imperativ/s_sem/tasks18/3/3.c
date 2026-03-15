#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void radixPass(int* a, int* b, int* r, int n, int K) {
    int* count = (int*)calloc(K + 1, sizeof(int));
    for (int i = 0; i < n; i++) count[r[a[i]]]++;
    for (int i = 0, sum = 0; i <= K; i++) {
        int t = count[i];
        count[i] = sum;
        sum += t;
    }
    for (int i = 0; i < n; i++) b[count[r[a[i]]]++] = a[i];
    free(count);
}

int leq2(int a1, int a2, int b1, int b2) {
    return (a1 < b1 || (a1 == b1 && a2 <= b2));
}

int leq3(int a1, int a2, int a3, int b1, int b2, int b3) {
    return (a1 < b1 || (a1 == b1 && leq2(a2, a3, b2, b3)));
}

void suffixArray(int* s, int* SA, int n, int K) {
    int n0 = (n + 2) / 3, n1 = (n + 1) / 3, n2 = n / 3;
    int n02 = n0 + n2;
    int* s12 = (int*)malloc((n02 + 3) * sizeof(int));
    int* SA12 = (int*)malloc((n02 + 3) * sizeof(int));
    int* s0 = (int*)malloc(n0 * sizeof(int));
    int* SA0 = (int*)malloc(n0 * sizeof(int));

    s12[n02] = s12[n02 + 1] = s12[n02 + 2] = 0;
    SA12[n02] = SA12[n02 + 1] = SA12[n02 + 2] = 0;

    for (int i = 0, j = 0; i < n + (n % 3 == 1); i++) {
        if (i % 3 != 0) s12[j++] = i;
    }

    radixPass(s12, SA12, s + 2, n02, K);
    radixPass(SA12, s12, s + 1, n02, K);
    radixPass(s12, SA12, s, n02, K);

    int name = 0, c0 = -1, c1 = -1, c2 = -1;
    for (int i = 0; i < n02; i++) {
        if (s[SA12[i]] != c0 || s[SA12[i] + 1] != c1 || s[SA12[i] + 2] != c2) {
            name++;
            c0 = s[SA12[i]]; c1 = s[SA12[i] + 1]; c2 = s[SA12[i] + 2];
        }
        if (SA12[i] % 3 == 1) s12[SA12[i] / 3] = name;
        else s12[SA12[i] / 3 + n0] = name;
    }

    if (name < n02) {
        suffixArray(s12, SA12, n02, name);
        for (int i = 0; i < n02; i++) s12[SA12[i]] = i + 1;
    } else {
        for (int i = 0; i < n02; i++) SA12[s12[i] - 1] = i;
    }

    for (int i = 0, j = 0; i < n02; i++) {
        if (SA12[i] < n0) s0[j++] = 3 * SA12[i];
    }
    radixPass(s0, SA0, s, n0, K);

    for (int p = 0, t = n0 - n1, k = 0; k < n; k++) {
        int i = (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2);
        int j = SA0[p];
        if (SA12[t] < n0 ? 
            leq2(s[i], s12[SA12[t] + n0], s[j], s12[j / 3]) :
            leq3(s[i], s[i + 1], s12[SA12[t] - n0 + 1], s[j], s[j + 1], s12[j / 3 + n0])) {
            SA[k] = i; t++;
            if (t == n02) for (k++; p < n0; p++, k++) SA[k] = SA0[p];
        } else {
            SA[k] = j; p++;
            if (p == n0) for (k++; t < n02; t++, k++) SA[k] = (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2);
        }
    }

    free(s12); free(SA12); free(s0); free(SA0);
}

int main() {
    freopen("input.txt", "r", stdin);

    char str[500005];
    scanf("%s", str);
    int n = strlen(str);
    int* s = malloc((n + 3) * sizeof(int));
    int* SA = malloc((n + 3) * sizeof(int));
    for (int i = 0; i < n; i++) s[i] = str[i] - 'a' + 1;
    s[n] = s[n + 1] = s[n + 2] = 0;

    suffixArray(s, SA, n, 26);

    for (int i = 0; i < n; i++) {
        printf("%d%c", SA[i], (i == n - 1 ? '\n' : ' '));
    }

    free(s); free(SA);
    return 0;
}