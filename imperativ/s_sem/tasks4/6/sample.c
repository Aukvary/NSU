#include "sample.h"
#include <assert.h>
#define TYPE double
#define NAME vector
#include "array_def.h"
#define TYPE int
#define NAME indices
#include "array_def.h"
int main()
{
    vector values;
    vector_init(&values);
    assert(values.n == 0);
    vector_push(&values, 1.0);
    vector_push(&values, 2.0);
    assert(values.n == 2 && values.arr[0] == 1.0 && values.arr[1] == 2.0);
    indices ids;
    indices_init(&ids);
    int temp[] = {1, 2, 3, 4, 5, 6};
    indices_insert(&ids, 0, temp, sizeof(temp) / sizeof(temp[0]));
    assert(ids.n == 6 && ids.arr[3] == 4);
    indices_insert(&ids, 4, temp, 5);
    assert(ids.n == 11 && ids.arr[3] == 4 && ids.arr[9] == 5);
    assert(ids.arr[4] == 1 && ids.arr[6] == 3 && ids.arr[8] == 5);
    indices_erase(&ids, 2, 5);
    assert(ids.n == 6 && ids.arr[0] == 1 && ids.arr[1] == 2);
    assert(ids.arr[2] == 4 && ids.arr[3] == 5 && ids.arr[4] == 5);
    indices_destroy(&ids); // memory freed
    indices_push(&ids, 13);
    assert(ids.n == 1 && ids.arr[0] == 13);
    indices_resize(&ids, 5, -1);
    assert(ids.n == 5 && ids.arr[0] == 13 && ids.arr[1] == -1);
    indices_reserve(&ids, 1000);
    int *ptr = &ids.arr[0];
    for (int i = 0; i < 900; i++)
        indices_push(&ids, i);
    assert(*ptr == 13 && ptr == &ids.arr[0]);
    for (int i = 0; i < 900; i++)
        indices_pop(&ids);
    assert(ptr == &ids.arr[0]); // never shrink buffer!
    indices_destroy(&ids);
}