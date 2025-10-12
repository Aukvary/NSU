#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int len;
    char sign; 
    char arr[101]; 
} LongNum;

LongNum newLongNum(int val) {
    LongNum num = {0, 0, {0}};
    
    if (val == 0) {
        num.len = 1;
        return num;
    }
    
    if (val < 0) {
        num.sign = 1;
        val = -val;
    }
    
    while (val > 0) {
        num.arr[num.len++] = val % 10;
        val /= 10;
    }
    
    return num;
}

LongNum newLongNumFromString(const char* str) {
    LongNum num = {0, 0, {0}};
    int len = strlen(str);
    
    int start = 0;
    if (str[0] == '-') {
        num.sign = 1;
        start = 1;
    }
    
    for (int i = len - 1; i >= start; i--) {
        if (isdigit(str[i])) {
            num.arr[num.len++] = str[i] - '0';
        }
    }
    
    while (num.len > 1 && num.arr[num.len - 1] == 0) {
        num.len--;
    }
    
    if (num.len == 1 && num.arr[0] == 0) {
        num.sign = 0;
    }
    
    return num;
}

int compareAbs(const LongNum* v1, const LongNum* v2) {
    if (v1->len != v2->len) {
        return (v1->len > v2->len) ? 1 : -1;
    }
    
    for (int i = v1->len - 1; i >= 0; i--) {
        if (v1->arr[i] != v2->arr[i]) {
            return (v1->arr[i] > v2->arr[i]) ? 1 : -1;
        }
    }
    
    return 0;
}

LongNum addAbs(const LongNum* v1, const LongNum* v2) {
    int len = MAX(v1->len, v2->len);
    LongNum num = {len, 0, {0}};
    
    int carry = 0;
    for (int i = 0; i < len; i++) {
        int digit1 = (i < v1->len) ? v1->arr[i] : 0;
        int digit2 = (i < v2->len) ? v2->arr[i] : 0;
        
        int sum = digit1 + digit2 + carry;
        num.arr[i] = sum % 10;
        carry = sum / 10;
    }
    
    if (carry > 0 && num.len < 100) {
        num.arr[num.len++] = carry;
    }
    
    return num;
}

LongNum subAbs(const LongNum* v1, const LongNum* v2) {
    LongNum num = {v1->len, 0, {0}};
    
    int borrow = 0;
    for (int i = 0; i < v1->len; i++) {
        int digit1 = v1->arr[i];
        int digit2 = (i < v2->len) ? v2->arr[i] : 0;
        
        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        num.arr[i] = diff;
    }
    
    while (num.len > 1 && num.arr[num.len - 1] == 0) {
        num.len--;
    }
    
    return num;
}

LongNum sum(const LongNum* v1, const LongNum* v2) {
    LongNum result;
    
    if (v1->sign == v2->sign) {
        result = addAbs(v1, v2);
        result.sign = v1->sign;
    } else {
        int cmp = compareAbs(v1, v2);
        if (cmp >= 0) {
            result = subAbs(v1, v2);
            result.sign = v1->sign;
        } else {
            result = subAbs(v2, v1);
            result.sign = v2->sign;
        }
    }
    
    if (result.len == 1 && result.arr[0] == 0) {
        result.sign = 0;
    }
    
    return result;
}

LongNum sub(const LongNum* v1, const LongNum* v2) {
    LongNum v2_opposite = *v2;
    v2_opposite.sign = !v2_opposite.sign;
    
    return sum(v1, &v2_opposite);
}

LongNum mult(const LongNum* v1, int v2) {
    if (v2 == 0) {
        LongNum zero = {1, 0, {0}};
        return zero;
    }
    
    LongNum num = {v1->len, 0, {0}};
    
    num.sign = v1->sign;
    if (v2 < 0) {
        num.sign = !num.sign;
        v2 = -v2;
    }
    
    int carry = 0;
    for (int i = 0; i < v1->len; i++) {
        int product = v1->arr[i] * v2 + carry;
        num.arr[i] = product % 10;
        carry = product / 10;
    }
    
    while (carry > 0 && num.len < 100) {
        num.arr[num.len++] = carry % 10;
        carry /= 10;
    }
    
    if (num.len == 1 && num.arr[0] == 0) {
        num.sign = 0;
    }
    
    return num;
}

LongNum multLong(const LongNum* v1, const LongNum* v2) {
    if ((v1->len == 1 && v1->arr[0] == 0) || (v2->len == 1 && v2->arr[0] == 0)) {
        LongNum zero = {1, 0, {0}};
        return zero;
    }
    
    LongNum result = {1, 0, {0}}; 
    
    result.sign = v1->sign ^ v2->sign;
    
    for (int i = 0; i < v2->len; i++) {
        LongNum temp = mult(v1, v2->arr[i]);
        
        LongNum shifted = {temp.len + i, temp.sign, {0}};
        for (int j = 0; j < i; j++) {
            shifted.arr[j] = 0;
        }
        for (int j = 0; j < temp.len; j++) {
            shifted.arr[j + i] = temp.arr[j];
        }
        
        LongNum new_result = addAbs(&result, &shifted);
        new_result.sign = result.sign; 
        result = new_result;
    }
    
    if (result.len == 1 && result.arr[0] == 0) {
        result.sign = 0;
    }
    
    return result;
}

int main() {
    FILE* in = fopen("input.txt", "r");

    int n;
    fscanf(in, "%d", &n);
    
    LongNum* nums = (LongNum*)calloc(n, sizeof(LongNum));
    char buf[200];
    
    fgets(buf, sizeof(buf), in);
    
    for (int i = 0; i < n; i++) {
        if (!fgets(buf, sizeof(buf), in)) 
            break;
        
        char* mode = strtok(buf, " \n");
        
        switch (mode[0]) {
            case '0': { 
                char* num_str = strtok(NULL, " \n");
                nums[i] = newLongNumFromString(num_str);
                break;
            }
            
            case '1': { 
                char* a_str = strtok(NULL, " \n");
                char* b_str = strtok(NULL, " \n");
                int a = atoi(a_str);
                int b = atoi(b_str);
                nums[i] = sum(&nums[a], &nums[b]);
                break;
            }
            
            case '2': { 
                char* a_str = strtok(NULL, " \n");
                char* b_str = strtok(NULL, " \n");
                int a = atoi(a_str);
                int b = atoi(b_str);
                nums[i] = sub(&nums[a], &nums[b]);
                break;
            }
            
            case '3': {
                char* a_str = strtok(NULL, " \n");
                char* b_str = strtok(NULL, " \n");
                int a = atoi(a_str);
                int b = atoi(b_str);
                nums[i] = multLong(&nums[a], &nums[b]);
                break;
            }
        }
    }
    
    
    for (int i = 0; i < n; i++) {
        if (nums[i].sign) {
            printf("-");
        }
        for (int j = nums[i].len - 1; j >= 0; j--) {
            printf("%d", nums[i].arr[j]);
        }
        printf("\n");
    }
    
    return 0;
}