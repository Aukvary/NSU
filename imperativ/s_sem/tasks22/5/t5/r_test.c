#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include "priority_queue.h"

static int free_counter;

static void free_item(void *data) {
    free_counter++;
    free(data);
}

static int *make_int(int x) {
    int *p = (int *)malloc(sizeof(int));
    assert_non_null(p);
    *p = x;
    return p;
}

static void test_create_destroy(void **state) {
    priority_queue_t *q = pq_create(10);
    assert_non_null(q);
    assert_true(pq_is_empty(q));
    assert_false(pq_is_full(q));
    pq_destroy(q, NULL);
}

static void test_create_unlimited(void **state) {
    priority_queue_t *q = pq_create(0);
    assert_non_null(q);
    assert_true(pq_is_empty(q));
    assert_false(pq_is_full(q));
    pq_destroy(q, NULL);
}

static void test_create_capacity_one(void **state) {
    priority_queue_t *q = pq_create(1);
    assert_non_null(q);
    assert_true(pq_push(q, NULL, 5));
    assert_true(pq_is_full(q));
    pq_destroy(q, NULL);
}

static void test_push(void **state) {
    priority_queue_t *q = pq_create(3);
    assert_true(pq_push(q, NULL, 1));
    assert_true(pq_push(q, NULL, 2));
    assert_int_equal(pq_size(q), 2);
    pq_destroy(q, NULL);
}

static void test_push_pop_priority(void **state) {
    priority_queue_t *q = pq_create(10);
    void *data;
    int pr;

    pq_push(q, (void *)1, 10);
    pq_push(q, (void *)2, 30);
    pq_push(q, (void *)3, 20);

    assert_true(pq_pop(q, &data, &pr));
    assert_int_equal((intptr_t)data, 2);
    assert_int_equal(pr, 30);

    assert_true(pq_pop(q, &data, &pr));
    assert_int_equal((intptr_t)data, 3);
    assert_int_equal(pr, 20);

    assert_true(pq_pop(q, &data, &pr));
    assert_int_equal((intptr_t)data, 1);
    assert_int_equal(pr, 10);

    pq_destroy(q, NULL);
}

static void test_peek(void **state) {
    priority_queue_t *q = pq_create(10);
    void *data;
    int pr;

    pq_push(q, (void *)7, 100);
    assert_true(pq_peek(q, &data, &pr));
    assert_int_equal((intptr_t)data, 7);
    assert_int_equal(pr, 100);
    assert_int_equal(pq_size(q), 1);

    pq_destroy(q, NULL);
}

static void test_overflow(void **state) {
    priority_queue_t *q = pq_create(2);

    assert_true(pq_push(q, NULL, 1));
    assert_true(pq_push(q, NULL, 2));
    assert_false(pq_push(q, NULL, 3));

    pq_destroy(q, NULL);
}

static void test_clear(void **state) {
    priority_queue_t *q = pq_create(5);
    int *a = make_int(1);
    int *b = make_int(2);

    free_counter = 0;
    pq_push(q, a, 1);
    pq_push(q, b, 2);
    pq_clear(q, free_item);

    assert_true(pq_is_empty(q));
    assert_int_equal(free_counter, 2);

    pq_destroy(q, NULL);
}

static void test_empty_operations(void **state) {
    priority_queue_t *q = pq_create(3);
    assert_false(pq_pop(q, NULL, NULL));
    assert_false(pq_peek(q, NULL, NULL));
    pq_destroy(q, NULL);
}

static void test_equal_priorities(void **state) {
    priority_queue_t *q = pq_create(5);
    int pr1, pr2;

    pq_push(q, (void *)1, 10);
    pq_push(q, (void *)2, 10);

    assert_true(pq_pop(q, NULL, &pr1));
    assert_true(pq_pop(q, NULL, &pr2));
    assert_int_equal(pr1, 10);
    assert_int_equal(pr2, 10);

    pq_destroy(q, NULL);
}

static void test_unlimited_queue(void **state) {
    priority_queue_t *q = pq_create(0);
    int pr;

    assert_true(pq_push(q, NULL, 1));
    assert_true(pq_push(q, NULL, 5));
    assert_true(pq_push(q, NULL, 3));
    assert_int_equal(pq_size(q), 3);

    assert_true(pq_pop(q, NULL, &pr));
    assert_int_equal(pr, 5);

    pq_destroy(q, NULL);
}

static void test_null_queue(void **state) {
    assert_false(pq_push(NULL, NULL, 1));
    assert_false(pq_pop(NULL, NULL, NULL));
    assert_false(pq_peek(NULL, NULL, NULL));
    assert_int_equal(pq_size(NULL), 0);
    assert_true(pq_is_empty(NULL));
    assert_false(pq_is_full(NULL));
    pq_clear(NULL, NULL);
    pq_destroy(NULL, NULL);
}

static void test_clear_no_free(void **state) {
    priority_queue_t *q = pq_create(3);
    pq_push(q, (void *)1, 1);
    pq_push(q, (void *)2, 2);
    pq_clear(q, NULL);
    assert_true(pq_is_empty(q));
    pq_destroy(q, NULL);
}

static void test_pop_peek_null_params(void **state) {
    priority_queue_t *q = pq_create(2);
    pq_push(q, (void *)1, 5);
    assert_true(pq_peek(q, NULL, NULL));
    assert_true(pq_pop(q, NULL, NULL));
    pq_destroy(q, NULL);
}

static void test_pop_only_data(void **state) {
    priority_queue_t *q = pq_create(2);
    void *data;

    pq_push(q, (void *)123, 9);
    assert_true(pq_pop(q, &data, NULL));
    assert_int_equal((intptr_t)data, 123);

    pq_destroy(q, NULL);
}

static void test_pop_only_priority(void **state) {
    priority_queue_t *q = pq_create(2);
    int pr;

    pq_push(q, (void *)123, 9);
    assert_true(pq_pop(q, NULL, &pr));
    assert_int_equal(pr, 9);

    pq_destroy(q, NULL);
}

static void test_peek_only_data(void **state) {
    priority_queue_t *q = pq_create(2);
    void *data;

    pq_push(q, (void *)55, 4);
    assert_true(pq_peek(q, &data, NULL));
    assert_int_equal((intptr_t)data, 55);

    pq_destroy(q, NULL);
}

static void test_peek_only_priority(void **state) {
    priority_queue_t *q = pq_create(2);
    int pr;

    pq_push(q, (void *)55, 4);
    assert_true(pq_peek(q, NULL, &pr));
    assert_int_equal(pr, 4);

    pq_destroy(q, NULL);
}

static void test_heapify_up_single_element(void **state) {
    priority_queue_t *q = pq_create(1);
    int pr;

    pq_push(q, NULL, 42);
    assert_true(pq_peek(q, NULL, &pr));
    assert_int_equal(pr, 42);

    pq_destroy(q, NULL);
}

static void test_heapify_down_single_element(void **state) {
    priority_queue_t *q = pq_create(2);
    int pr;

    pq_push(q, NULL, 10);
    pq_push(q, NULL, 5);
    pq_pop(q, NULL, NULL);
    assert_true(pq_peek(q, NULL, &pr));
    assert_int_equal(pr, 5);

    pq_destroy(q, NULL);
}

static void test_destroy_no_free(void **state) {
    priority_queue_t *q = pq_create(2);
    pq_push(q, (void *)1, 1);
    pq_destroy(q, NULL);
}

static void test_destroy_frees_queue(void **state) {
    priority_queue_t *q = pq_create(3);
    int *a = make_int(1);
    int *b = make_int(2);

    free_counter = 0;
    pq_push(q, a, 1);
    pq_push(q, b, 2);
    pq_destroy(q, free_item);

    assert_int_equal(free_counter, 2);
}

static void test_clear_resets_capacity(void **state) {
    priority_queue_t *q = pq_create(2);

    pq_push(q, NULL, 1);
    pq_push(q, NULL, 2);
    pq_clear(q, NULL);

    assert_true(pq_is_empty(q));
    assert_false(pq_is_full(q));
    assert_true(pq_push(q, NULL, 3));

    pq_destroy(q, NULL);
}

static void test_pop_clears_last_element(void **state) {
    priority_queue_t *q = pq_create(1);

    pq_push(q, NULL, 7);
    assert_true(pq_pop(q, NULL, NULL));
    assert_true(pq_is_empty(q));

    pq_destroy(q, NULL);
}

static void test_heap_stability_up(void **state) {
    priority_queue_t *q = pq_create(10);
    int pr;

    pq_push(q, NULL, 1);
    pq_push(q, NULL, 2);
    pq_push(q, NULL, 3);
    pq_push(q, NULL, 4);

    assert_true(pq_peek(q, NULL, &pr));
    assert_int_equal(pr, 4);

    pq_destroy(q, NULL);
}

static void test_heap_stability_down(void **state) {
    priority_queue_t *q = pq_create(10);
    int pr;

    pq_push(q, NULL, 10);
    pq_push(q, NULL, 7);
    pq_push(q, NULL, 8);
    pq_pop(q, NULL, NULL);

    assert_true(pq_peek(q, NULL, &pr));
    assert_int_equal(pr, 8);

    pq_destroy(q, NULL);
}

static void test_unlimited_queue_realloc(void **state) {
    priority_queue_t *q = pq_create(0);
    int pr;
    int i;

    for (i = 0; i < 100; i++) {
        assert_true(pq_push(q, NULL, i));
    }

    assert_int_equal(pq_size(q), 100);
    assert_true(pq_pop(q, NULL, &pr));
    assert_int_equal(pr, 99);

    pq_destroy(q, NULL);
}

static void test_push_checks_overflow(void **state) {
    priority_queue_t *q = pq_create(1);

    assert_true(pq_push(q, NULL, 1));
    assert_false(pq_push(q, NULL, 2));

    pq_destroy(q, NULL);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_create_destroy),
        cmocka_unit_test(test_create_unlimited),
        cmocka_unit_test(test_create_capacity_one),
        cmocka_unit_test(test_push),
        cmocka_unit_test(test_push_pop_priority),
        cmocka_unit_test(test_peek),
        cmocka_unit_test(test_overflow),
        cmocka_unit_test(test_clear),
        cmocka_unit_test(test_empty_operations),
        cmocka_unit_test(test_equal_priorities),
        cmocka_unit_test(test_unlimited_queue),
        cmocka_unit_test(test_null_queue),
        cmocka_unit_test(test_clear_no_free),
        cmocka_unit_test(test_pop_peek_null_params),
        cmocka_unit_test(test_pop_only_data),
        cmocka_unit_test(test_pop_only_priority),
        cmocka_unit_test(test_peek_only_data),
        cmocka_unit_test(test_peek_only_priority),
        cmocka_unit_test(test_heapify_up_single_element),
        cmocka_unit_test(test_heapify_down_single_element),
        cmocka_unit_test(test_destroy_no_free),
        cmocka_unit_test(test_destroy_frees_queue),
        cmocka_unit_test(test_clear_resets_capacity),
        cmocka_unit_test(test_pop_clears_last_element),
        cmocka_unit_test(test_heap_stability_up),
        cmocka_unit_test(test_heap_stability_down),
        cmocka_unit_test(test_unlimited_queue_realloc),
        cmocka_unit_test(test_push_checks_overflow),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}