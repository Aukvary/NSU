#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pref_arr(const char* t, int n, int* pref) {
	pref[0] = 0;   
	for (int i = 1; i < n; i++) {
		int j = pref[i - 1];

		while (j > 0 && t[i] != t[j]) {
			j = pref[j - 1];
		}

		if (t[i] == t[j]) {
			j += 1;
		}

		pref[i] = j;
	}
}

int sub_text(const char* str, const char* t) {
	int tlen = strlen(t);
	int* pref = malloc((tlen + 1) * sizeof(int));

	pref_arr(t, tlen, pref);

	int len = 0;
	int count = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		while (len > 0 && str[i] != t[len]) {
			len = pref[len];
		}

		if (str[i] == t[len]) {
			len++;
		}

		if (len == tlen) {
			count++;
			len = pref[len - 1];
		}
	}

	return count;
}