#include <stdio.h>
#include <string.h>

int cmp(const char* a, const char* b) {
    int len_a = strlen(a);
    int len_b = strlen(b);

    if (len_a != len_b) {
        return len_a - len_b;
    }
    return strcmp(a, b);
}

void subtract(char* a, const char* b) {
    int len_a = strlen(a);
    int len_b = strlen(b);

    int borrow = 0;
    int i = len_a - 1;
    int j = len_b - 1;

    while (i >= 0) {
        int digit_a = a[i] - '0';
        int digit_b = (j >= 0) ? b[j] - '0' : 0;
        int diff = digit_a - digit_b - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        a[i] = diff + '0';
        i--;
        j--;
    }

    int start = 0;
    while (a[start] == '0' && start < len_a - 1) {
        start++;
    }
    if (start > 0) {
        memmove(a, a + start, len_a - start + 1);
    }
}

int main() {
    FILE* in = fopen("input.txt", "r");

    char buf[3000] = { 0 };
    int len = fread(buf, 1, sizeof(buf) - 1, in);
    fclose(in);
    buf[len] = '\0';

    int len1 = 0;
    while (len1 < len && buf[len1] != '\n') {
        len1++;
    }

    int len2 = len - len1 - 1;

    char* num1 = buf;
    char* num2 = buf + len1 + 1;

    while (len1 > 0 && (num1[len1-1] == '\n' || num1[len1-1] == '\r')) len1--;
    num1[len1] = '\0';
    while (len2 > 0 && (num2[len2-1] == '\n' || num2[len2-1] == '\r')) len2--;
    num2[len2] = '\0';

    if (cmp(num1, num2) < 0) {
        printf("0");
        return 0;
    }

    char result[2002] = {0};
    int result_len = 0;

    char current[2002] = {0};
    int current_len = 0;

    int pos = 0;
    int total_len = strlen(num1);

    while (pos < total_len) {
        if (current_len < sizeof(current) - 1) {
            current[current_len++] = num1[pos];
            current[current_len] = '\0';
        }

        int start_idx = 0;
        while (start_idx < current_len - 1 && current[start_idx] == '0') {
            start_idx++;
        }
        if (start_idx > 0) {
            memmove(current, current + start_idx, current_len - start_idx + 1);
            current_len -= start_idx;
        }

        if (cmp(current, num2) < 0) {
            if (result_len > 0) {
                result[result_len++] = '0';
            }
            pos++;
            continue;
        }

        int digit = 0;

        while (digit < 9) {
            char product[2002] = {0};
            int carry = 0;
            int product_len = strlen(num2);

            for (int i = product_len - 1; i >= 0; i--) {
                int p = (num2[i] - '0') * (digit + 1) + carry;
                product[i] = (p % 10) + '0';
                carry = p / 10;
            }

            if (carry > 0) {
                memmove(product + 1, product, product_len);
                product[0] = carry + '0';
                product_len++;
            }
            product[product_len] = '\0';

            if (cmp(product, current) > 0) {
                break;
            }

            digit++;
        }

        result[result_len++] = digit + '0';

        if (digit > 0) {
            char multiple[2002] = {0};
            int carry = 0;
            int multiple_len = strlen(num2);

            for (int i = multiple_len - 1; i >= 0; i--) {
                int p = (num2[i] - '0') * digit + carry;
                multiple[i] = (p % 10) + '0';
                carry = p / 10;
            }

            if (carry > 0) {
                memmove(multiple + 1, multiple, multiple_len);
                multiple[0] = carry + '0';
                multiple_len++;
            }
            multiple[multiple_len] = '\0';

            subtract(current, multiple);
            current_len = strlen(current);
        }

        pos++;
    }

    if (result_len == 0) {
        result[result_len++] = '0';
    }
    result[result_len] = '\0';

    int start_idx = 0;
    while (start_idx < result_len - 1 && result[start_idx] == '0') {
        start_idx++;
    }

    printf("%s", result + start_idx);

    return 0;
}
