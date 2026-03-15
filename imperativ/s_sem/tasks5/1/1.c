#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#pragma comment (linker, "/STACK: 50000000")

char *ptr;

double parse_expression();
double parse_term();
double parse_factor();
double parse_number();

double parse_number() {
    while (isspace(*ptr)) ptr++;
    double res = 0;
    int sign = 1;
    
    if (*ptr == '-') {
        sign = -1;
        ptr++;
        while (isspace(*ptr)) ptr++;
    }

    if (*ptr == '(') {
        ptr++;
        res = parse_expression();
        while (isspace(*ptr)) ptr++;
        if (*ptr == ')') ptr++;
        return res * sign;
    }

    while (isdigit(*ptr)) {
        res = res * 10 + (*ptr - '0');
        ptr++;
    }
    return res * sign;
}

double parse_factor() {
    return parse_number();
}

double parse_term() {
    double res = parse_factor();
    while (isspace(*ptr)) ptr++;
    while (*ptr == '*' || *ptr == '/') {
        char op = *ptr;
        ptr++;
        double next = parse_factor();
        if (op == '*') res *= next;
        else res /= next;
        while (isspace(*ptr)) ptr++;
    }
    return res;
}

double parse_expression() {
    double res = parse_term();
    while (isspace(*ptr)) ptr++;
    while (*ptr == '+' || *ptr == '-') {
        char op = *ptr;
        ptr++;
        double next = parse_term();
        if (op == '+') res += next;
        else res -= next;
        while (isspace(*ptr)) ptr++;
    }
    return res;
}

int main() {
    static char buf[500005];
    freopen("input.txt", "r", stdin);

    if (fgets(buf, sizeof(buf), stdin)) {
        ptr = buf;
        double result = parse_expression();
        printf("%.20lf\n", result);
    }

    return 0;
}