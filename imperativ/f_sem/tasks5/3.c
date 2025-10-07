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

}