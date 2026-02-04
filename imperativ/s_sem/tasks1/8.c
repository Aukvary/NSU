#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long i64;

typedef struct {
    char digits[500];  
    int len;
} LongNum;

LongNum long_num_new(i64 num) {
    LongNum long_num = {0};
    
    if (num == 0) {
        long_num.digits[0] = 0;
        long_num.len = 1;
        return long_num;
    }
    
    while (num > 0) {
        long_num.digits[long_num.len++] = num % 10;
        num /= 10;
    }
    
    return long_num;
}

int long_num_is_zero(const LongNum* num) {
    return num->len == 1 && num->digits[0] == 0;
}

int long_num_is_one(const LongNum* num) {
    return num->len == 1 && num->digits[0] == 1;
}

int long_num_cmp(const LongNum* a, const LongNum* b) {
    if (a->len != b->len) {
        return a->len > b->len ? 1 : -1;
    }
    
    for (int i = a->len - 1; i >= 0; i--) {
        if (a->digits[i] != b->digits[i]) {
            return a->digits[i] > b->digits[i] ? 1 : -1;
        }
    }
    
    return 0;
}

LongNum long_num_add(const LongNum* a, const LongNum* b) {
    LongNum res = {0};
    int carry = 0;
    int max_len = a->len > b->len ? a->len : b->len;
    
    for (int i = 0; i < max_len; i++) {
        int sum = carry;
        if (i < a->len) sum += a->digits[i];
        if (i < b->len) sum += b->digits[i];
        res.digits[res.len++] = sum % 10;
        carry = sum / 10;
    }
    
    if (carry) {
        res.digits[res.len++] = carry;
    }
    
    return res;
}

LongNum long_num_sub(const LongNum* a, const LongNum* b) {
    LongNum res = {0};
    int borrow = 0;
    
    for (int i = 0; i < a->len; i++) {
        int diff = a->digits[i] - borrow;
        if (i < b->len) diff -= b->digits[i];
        
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        res.digits[res.len++] = diff;
    }
    
    while (res.len > 1 && res.digits[res.len - 1] == 0) {
        res.len--;
    }
    
    return res;
}

LongNum long_num_mult_digit(const LongNum* num, int digit) {
    LongNum result = {0};
    
    if (digit == 0) {
        result.digits[0] = 0;
        result.len = 1;
        return result;
    }
    
    int carry = 0;
    for (int i = 0; i < num->len; i++) {
        int product = num->digits[i] * digit + carry;
        result.digits[result.len++] = product % 10;
        carry = product / 10;
    }
    
    if (carry > 0) {
        result.digits[result.len++] = carry;
    }
    
    return result;
}

LongNum long_num_div_by_2(const LongNum* num) {
    LongNum result = {0};
    int carry = 0;
    
    result.len = num->len;
    for (int i = num->len - 1; i >= 0; i--) {
        int current = carry * 10 + num->digits[i];
        result.digits[i] = current / 2;
        carry = current % 2;
    }
    
    while (result.len > 1 && result.digits[result.len - 1] == 0) {
        result.len--;
    }
    
    return result;
}

LongNum long_num_mult(const LongNum* a, const LongNum* b) {
    LongNum result = long_num_new(0);
    
    for (int i = 0; i < b->len; i++) {
        LongNum temp = long_num_mult_digit(a, b->digits[i]);
        
        LongNum shifted = {0};
        shifted.len = temp.len + i;
        for (int j = 0; j < i; j++) {
            shifted.digits[j] = 0;
        }
        for (int j = 0; j < temp.len; j++) {
            shifted.digits[j + i] = temp.digits[j];
        }
        
        result = long_num_add(&result, &shifted);
    }
    
    return result;
}

LongNum long_num_mod(const LongNum* a, const LongNum* b) {
    if (long_num_is_zero(b)) {
        LongNum zero = long_num_new(0);
        return zero;
    }
    
    if (long_num_cmp(a, b) < 0) {
        LongNum copy = *a;
        return copy;
    }
    
    LongNum remainder = *a;
    
    while (long_num_cmp(&remainder, b) >= 0) {
        LongNum temp = *b;
        
        while (long_num_cmp(&remainder, &temp) >= 0) {
            LongNum shifted = {0};
            shifted.len = temp.len + 1;
            shifted.digits[0] = 0;
            for (int j = 0; j < temp.len; j++) {
                shifted.digits[j + 1] = temp.digits[j];
            }
            temp = shifted;
        }
        
        LongNum correct = {0};
        correct.len = temp.len - 1;
        for (int j = 0; j < correct.len; j++) {
            correct.digits[j] = temp.digits[j + 1];
        }
        temp = correct;
        
        while (long_num_cmp(&remainder, &temp) >= 0) {
            remainder = long_num_sub(&remainder, &temp);
        }
    }
    
    return remainder;
}

LongNum long_num_mul_mod(const LongNum* a, const LongNum* b, const LongNum* mod) {
    LongNum result = long_num_new(0);
    LongNum a_mod = long_num_mod(a, mod);
    LongNum b_copy = *b;
    
    while (!long_num_is_zero(&b_copy)) {
        if (b_copy.digits[0] % 2 == 1) {
            result = long_num_add(&result, &a_mod);
            result = long_num_mod(&result, mod);
        }
        
        a_mod = long_num_add(&a_mod, &a_mod);
        a_mod = long_num_mod(&a_mod, mod);
        
        b_copy = long_num_div_by_2(&b_copy);
    }
    
    return result;
}

LongNum long_num_div(const LongNum* a, const LongNum* b) {
    if (long_num_is_zero(b)) {
        LongNum zero = long_num_new(0);
        return zero;
    }
    
    if (long_num_cmp(a, b) < 0) {
        LongNum zero = long_num_new(0);
        return zero;
    }
    
    LongNum quotient = long_num_new(0);
    LongNum remainder = *a;
    LongNum divisor = *b;
    
    int shift = a->len - b->len;
    if (shift < 0) shift = 0;
    
    while (shift >= 0) {
        LongNum shifted_divisor = {0};
        shifted_divisor.len = divisor.len + shift;
        
        for (int i = 0; i < shift; i++) {
            shifted_divisor.digits[i] = 0;
        }
        
        for (int i = 0; i < divisor.len; i++) {
            shifted_divisor.digits[i + shift] = divisor.digits[i];
        }
        
        int count = 0;
        while (long_num_cmp(&remainder, &shifted_divisor) >= 0) {
            remainder = long_num_sub(&remainder, &shifted_divisor);
            count++;
        }
        
        if (count > 0) {
            LongNum shifted_digit = {0};
            shifted_digit.len = shift + 1;
            
            for (int i = 0; i < shift; i++) {
                shifted_digit.digits[i] = 0;
            }
            shifted_digit.digits[shift] = count;
            
            quotient = long_num_add(&quotient, &shifted_digit);
        }
        
        shift--;
    }
    
    return quotient;
}

LongNum long_num_mod_inv(const LongNum* a, const LongNum* m) {
    LongNum m0 = *m;
    LongNum y = long_num_new(0);
    LongNum x = long_num_new(1);
    
    LongNum one = long_num_new(1);
    LongNum zero = long_num_new(0);
    
    if (long_num_is_one(m)) {
        return zero;
    }
    
    LongNum a_copy = long_num_mod(a, m);
    
    while (long_num_cmp(&a_copy, &one) > 0) {
        if (long_num_is_zero(&a_copy)) {
            return zero;
        }
        
        LongNum q = long_num_div(&m0, &a_copy);
        LongNum t = a_copy;
        
        LongNum qa = long_num_mult(&q, &a_copy);
        a_copy = long_num_sub(&m0, &qa);
        
        m0 = t;
        t = x;
        
        LongNum qx = long_num_mult(&q, &x);
        x = long_num_sub(&y, &qx);
        
        y = t;
    }
    
    if (long_num_cmp(&x, &zero) < 0) {
        x = long_num_add(&x, m);
    }
    
    return x;
}

void long_num_print(const LongNum* num) {
    if (num->len == 0) {
        printf("0");
        return;
    }
    
    for (int i = num->len - 1; i >= 0; i--) {
        printf("%d", num->digits[i]);
    }
}

int main(void) {
    freopen("input.txt", "r", stdin);
    
    int k;
    scanf("%d", &k);
    
    LongNum* ms = malloc(k * sizeof(LongNum));
    LongNum* as = malloc(k * sizeof(LongNum));
    
    for (int i = 0; i < k; i++) {
        long long temp;
        scanf("%lld", &temp);
        ms[i] = long_num_new(temp);
    }
    
    for (int i = 0; i < k; i++) {
        long long temp;
        scanf("%lld", &temp);
        as[i] = long_num_new(temp);
    }
    
    LongNum m = long_num_new(1);
    for (int i = 0; i < k; i++) {
        LongNum temp = long_num_mult(&m, &ms[i]);
        m = temp;
    }
    
    LongNum x = long_num_new(0);
    
    for (int i = 0; i < k; i++) {
        LongNum Mi = long_num_div(&m, &ms[i]);
        
        LongNum Mi_mod = long_num_mod(&Mi, &ms[i]);
        LongNum inv = long_num_mod_inv(&Mi_mod, &ms[i]);
        
        LongNum term1 = long_num_mul_mod(&as[i], &Mi, &m);
        LongNum term = long_num_mul_mod(&term1, &inv, &m);
        
        LongNum new_x = long_num_add(&x, &term);
        x = long_num_mod(&new_x, &m);
    }
    
    x = long_num_mod(&x, &m);
    
    long_num_print(&x);
    printf("\n");
    
    free(ms);
    free(as);
    return 0;
}