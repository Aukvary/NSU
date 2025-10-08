#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Label_s {
    char name[16]; // имя автора (заканчивается нулём)
    int age; // возраст автора (сколько лет)
} Label;

typedef struct NameStats_s {
    int cntTotal; // сколько всего подписей
    int cntLong; // сколько подписей с именами длиннее 10 букв
} NameStats;

typedef struct AgeStats_s {
    int cntTotal; // сколько всего подписей
    int cntAdults; // сколько подписей взрослых (хотя бы 18 лет)
    int cntKids; // сколько подписей детей (меньше 14 лет)
} AgeStats;

void calcStats(const Label* arr, int cnt, NameStats* oNames, AgeStats* oAges) {
    oNames->cntTotal = cnt;
    oNames->cntLong = 0;

    oAges->cntTotal = cnt;
    oAges->cntAdults = 0;
    oAges->cntKids = 0;

    for (int i = 0;i < cnt;i++) {
        if (strlen(arr[i].name) > 10) oNames->cntLong++;
        if (arr[i].age >= 18) oAges->cntAdults++;
        if (arr[i].age < 14) oAges->cntKids++;
    }
}

int main() {
    int n;
    int age;
    char name[16];
    char stash[4];
    FILE* in = fopen("input.txt", "r");
    fscanf(in, "%d", &n);
    Label* arr = calloc(n, sizeof(Label));
    for (int i = 0; i < n; i++) {
        fscanf(in, "%s %d %s", name, &age, stash);
        arr[i].age = age;
        strcpy(arr[i].name, name);
    }
    NameStats ns = { 0, 0 };
    AgeStats as = { 0, 0, 0 };
    calcStats(arr, n, &ns, &as);

    printf("names: total = %d\n", ns.cntTotal);
    printf("names: long = %d\n", ns.cntLong);
    printf("ages: total = %d\n", as.cntTotal);
    printf("ages: adult = %d\n", as.cntAdults);
    printf("ages: kid = %d\n", as.cntKids);

    return 0;
}