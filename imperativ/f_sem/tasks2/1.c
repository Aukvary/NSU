#include <stdio.h>
#include <string.h>

const char* days[7] = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};

int main(void) {
    char buf[11];
    scanf("%10s", &buf);
    int res = 0;

    for (int i = 0; i < 7; i++) {
        int buf_len = strlen(buf);
        int day_len = strlen(days[i]);

        if (buf_len > day_len)
            continue;

        if (!strncmp(buf,days[i],buf_len)) {
            if (res != 0) {
                printf("Ambiguous");
                return 0;
            }
            
            res = i + 1;
        }
    }

    if (res) {
        printf("%d", res);
        return 0;
    }

    printf("%s", "Invalid");
    return 0;
}