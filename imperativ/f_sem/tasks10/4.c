#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_ELEMENTS 100
#define MAX_FORMULA_LENGTH 1000

typedef struct {
    char name[3]; 
    int count;
} Element;

Element elements[MAX_ELEMENTS];
int elements_count = 0;

int compare_elements(const void* a, const void* b) {
    return strcmp(((Element*)a)->name, ((Element*)b)->name);
}

void parse_formula(const char** formula, int multiplier) {
    while (**formula && **formula != ')') {
        if (**formula == '(') {
            (*formula)++;

            Element temp_elements[MAX_ELEMENTS];
            int temp_count = 0;
            memcpy(temp_elements, elements, sizeof(Element) * elements_count);
            temp_count = elements_count;

            elements_count = 0;
            parse_formula(formula, 1);

            int bracket_multiplier = 0;
            while (isdigit(**formula)) {
                bracket_multiplier = bracket_multiplier * 10 + (**formula - '0');
                (*formula)++;
            }
            if (bracket_multiplier == 0) bracket_multiplier = 1;

            for (int i = 0; i < elements_count; i++) {
                int found = 0;
                for (int j = 0; j < temp_count; j++) {
                    if (strcmp(elements[i].name, temp_elements[j].name) == 0) {
                        temp_elements[j].count += elements[i].count * bracket_multiplier;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(temp_elements[temp_count].name, elements[i].name);
                    temp_elements[temp_count].count = elements[i].count * bracket_multiplier;
                    temp_count++;
                }
            }

            memcpy(elements, temp_elements, sizeof(Element) * temp_count);
            elements_count = temp_count;
        } else {
            char element[3] = {0};
            element[0] = **formula;
            (*formula)++;

            if (**formula && islower(**formula)) {
                element[1] = **formula;
                (*formula)++;
            }

            int count = 0;
            while (isdigit(**formula)) {
                count = count * 10 + (**formula - '0');
                (*formula)++;
            }
            if (count == 0) count = 1;

            int found = 0;
            for (int i = 0; i < elements_count; i++) {
                if (strcmp(elements[i].name, element) == 0) {
                    elements[i].count += count * multiplier;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(elements[elements_count].name, element);
                elements[elements_count].count = count * multiplier;
                elements_count++;
            }
        }
    }

    if (**formula == ')') {
        (*formula)++; 
    }
}

char* countOfAtoms(char* formula) {
    elements_count = 0;
    const char* ptr = formula;
    parse_formula(&ptr, 1);

    qsort(elements, elements_count, sizeof(Element), compare_elements);

    static char result[1000];
    result[0] = '\0';

    for (int i = 0; i < elements_count; i++) {
        strcat(result, elements[i].name);
        if (elements[i].count > 1) {
            char count_str[10];
            sprintf(count_str, "%d", elements[i].count);
            strcat(result, count_str);
        }
    }

    return result;
}

int main() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    char formula[MAX_FORMULA_LENGTH];
    fscanf(input, "%s", formula);

    char* result = countOfAtoms(formula);
    fprintf(output, "%s\n", result);

    fclose(input);
    fclose(output);
    return 0;
}
