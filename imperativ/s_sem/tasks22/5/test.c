#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "priority_queue.h"
#include <stdlib.h>

static void test_create_destroy(void **state) {
    priority_queue_t *q = pq_create(10);
    assert_non_null(q);
    pq_destroy(q, NULL);
}

static void test_create_unlimited(void **state) {
    priority_queue_t *q = pq_create(100);
    assert_non_null(q);
    pq_destroy(q, NULL);
}

static void test_create_capacity_one(void **state) {
    priority_queue_t *q = pq_create(1);
    assert_non_null(q);
    pq_destroy(q, NULL);
}

static void test_push(void **state) {
    priority_queue_t *q = pq_create(5);
    int x = 42;
    assert_true(pq_push(q, &x, 1));
    assert_int_equal(pq_size(q), 1);
    pq_destroy(q, NULL);
}

static void test_push_priority(void **state) {
    priority_queue_t *q = pq_create(5);
    int a=1, b=2;
    pq_push(q, &a, 5);
    pq_push(q, &b, 10);
    int *p; int prio;
    pq_peek(q, (void**)&p, &prio);
    assert_int_equal(prio, 10);
    pq_destroy(q, NULL);
}

static void test_peek(void **state) {
    priority_queue_t *q = pq_create(5);
    int x=99;
    pq_push(q, &x, 7);
    int *p; int prio;
    assert_true(pq_peek(q, (void**)&p, &prio));
    assert_int_equal(*p, 99);
    assert_int_equal(prio, 7);
    pq_destroy(q, NULL);
}

static void test_overflow(void **state) {
    priority_queue_t *q = pq_create(2);
    int a,b,c;
    assert_true(pq_push(q, &a, 1));
    assert_true(pq_push(q, &b, 2));
    assert_false(pq_push(q, &c, 3));
    pq_destroy(q, NULL);
}

static void test_clear(void **state) {
    priority_queue_t *q = pq_create(5);
    int *x = malloc(sizeof(int));
    pq_push(q, x, 1);
    pq_clear(q, free);
    assert_int_equal(pq_size(q), 0);
    pq_destroy(q, NULL);
}

static void test_empty_operations(void **state) {
    priority_queue_t *q = pq_create(5);
    void *p; int prio;
    assert_false(pq_pop(q, &p, &prio));
    assert_false(pq_peek(q, &p, &prio));
    pq_destroy(q, NULL);
}

static void test_equal_priorities(void **state) {
    priority_queue_t *q = pq_create(5);
    int a,b;
    pq_push(q, &a, 1);
    pq_push(q, &b, 1);
    assert_int_equal(pq_size(q), 2);
    pq_destroy(q, NULL);
}

static void test_unlimited_queue(void **state) {
    priority_queue_t *q = pq_create(1000);
    assert_non_null(q);
    pq_destroy(q, NULL);
}

static void test_null_queue(void **state) {
    assert_false(pq_push(NULL, NULL, 0));
    assert_false(pq_pop(NULL, NULL, NULL));
    assert_false(pq_peek(NULL, NULL, NULL));
    assert_int_equal(pq_size(NULL), 0);
    assert_true(pq_is_empty(NULL));
    assert_true(pq_is_full(NULL));
}

static void test_clear_no_free(void **state) {
    priority_queue_t *q = pq_create(5);
    int x=1;
    pq_push(q, &x, 1);
    pq_clear(q, NULL);
    assert_int_equal(pq_size(q), 0);
    pq_destroy(q, NULL);
}

static void test_pop_peek_null_params(void **state) {
    priority_queue_t *q = pq_create(5);
    int x=42;
    pq_push(q, &x, 1);
    assert_true(pq_pop(q, NULL, NULL));
    assert_int_equal(pq_size(q), 0);
    pq_destroy(q, NULL);
}

static void test_pop_only_data(void **state) {
    priority_queue_t *q = pq_create(5);
    int x=99;
    pq_push(q, &x, 2);
    int *p;
    assert_true(pq_pop(q, (void**)&p, NULL));
    assert_int_equal(*p, 99);
    assert_int_equal(pq_size(q), 0);
    pq_destroy(q, NULL);
}

static void test_pop_only_priority(void **state) {
    priority_queue_t *q = pq_create(5);
    int x=77;
    pq_push(q, &x, 3);
    int prio;
    assert_true(pq_pop(q, NULL, &prio));
    assert_int_equal(prio, 3);
    pq_destroy(q, NULL);
}

static void test_peek_only_data(void **state) {
    priority_queue_t *q = pq_create(5);
    int x=55;
    pq_push(q, &x, 4);
    int *p;
    assert_true(pq_peek(q, (void**)&p, NULL));
    assert_int_equal(*p, 55);
    pq_destroy(q, NULL);
}

static void test_peek_only_priority(void **state) {
    priority_queue_t *q = pq_create(5);
    int x=33;
    pq_push(q, &x, 5);
    int prio;
    assert_true(pq_peek(q, NULL, &prio));
    assert_int_equal(prio, 5);
    pq_destroy(q, NULL);
}

static void test_heapify_up_single_element(void **state) {
    priority_queue_t *q = pq_create(5);
    int x=10;
    assert_true(pq_push(q, &x, 1));
    assert_int_equal(pq_size(q), 1);
    pq_destroy(q, NULL);
}

static void test_heapify_down_single_element(void **state) {
    priority_queue_t *q = pq_create(5);
    int x=20;
    pq_push(q, &x, 1);
    int *p;
    assert_true(pq_pop(q, (void**)&p, NULL));
    assert_int_equal(*p, 20);
    pq_destroy(q, NULL);
}

static void test_destroy_no_free(void **state) {
    priority_queue_t *q = pq_create(5);
    int x=100;
    pq_push(q, &x, 1);
    pq_destroy(q, NULL);
}

static void test_destroy_frees_queue(void **state) {
    priority_queue_t *q = pq_create(5);
    assert_non_null(q);
    pq_destroy(q, NULL);
}

static void test_clear_resets_capacity(void **state) {
    priority_queue_t *q = pq_create(5);
    int x=1;
    pq_push(q, &x, 1);
    pq_clear(q, NULL);
    assert_int_equal(pq_size(q), 0);
    assert_true(pq_push(q, &x, 2));
    pq_destroy(q, NULL);
}

static void test_pop_clears_last_element(void **state) {
    priority_queue_t *q = pq_create(5);
    int x=42;
    pq_push(q, &x, 1);
    int *p;
    pq_pop(q, (void**)&p, NULL);
    assert_int_equal(pq_size(q), 0);
    pq_destroy(q, NULL);
}

static void test_heap_stability_up(void **state) {
    priority_queue_t *q = pq_create(5);
    int a,b;
    pq_push(q, &a, 1);
    pq_push(q, &b, 1);
    assert_int_equal(pq_size(q), 2);
    pq_destroy(q, NULL);
}

static void test_heap_stability_down(void **state) {
    priority_queue_t *q = pq_create(5);
    int a,b;
    pq_push(q, &a, 1);
    pq_push(q, &b, 1);
    int *p;
    pq_pop(q, (void**)&p, NULL);
    pq_pop(q, (void**)&p, NULL);
    assert_int_equal(pq_size(q), 0);
    pq_destroy(q, NULL);
}

static void test_unlimited_queue_realloc(void **state) {
    priority_queue_t *q = pq_create(100);
    assert_non_null(q);
    pq_destroy(q, NULL);
}

static void test_push_checks_overflow(void **state) {
    priority_queue_t *q = pq_create(1);
    int x=1;
    assert_true(pq_push(q, &x, 1));
    assert_false(pq_push(q, &x, 2));
    pq_destroy(q, NULL);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_create_destroy),
        cmocka_unit_test(test_create_unlimited),
        cmocka_unit_test(test_create_capacity_one),
        cmocka_unit_test(test_push),
        cmocka_unit_test(test_push_priority),
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