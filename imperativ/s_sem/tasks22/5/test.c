#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include "priority_queue.h"
#include <stdint.h>

static int free_counter;

static void free_item(void *element_data) {
    free_counter++;
    free(element_data);
}

static int *make_int(int value) {
    int *pointer = (int *)malloc(sizeof(int));
    assert_non_null(pointer);
    *pointer = value;
    return pointer;
}

static void test_create_destroy(void **state) {
    priority_queue_t *queue_handle = pq_create(10);
    assert_non_null(queue_handle);
    assert_true(pq_is_empty(queue_handle));
    assert_false(pq_is_full(queue_handle));
    pq_destroy(queue_handle, NULL);
}

static void test_create_unlimited(void **state) {
    priority_queue_t *queue_handle = pq_create(0);
    assert_non_null(queue_handle);
    assert_true(pq_is_empty(queue_handle));
    assert_false(pq_is_full(queue_handle));
    pq_destroy(queue_handle, NULL);
}

static void test_create_capacity_one(void **state) {
    priority_queue_t *queue_handle = pq_create(1);
    assert_non_null(queue_handle);
    assert_true(pq_push(queue_handle, NULL, 5));
    assert_true(pq_is_full(queue_handle));
    pq_destroy(queue_handle, NULL);
}

static void test_push(void **state) {
    priority_queue_t *queue_handle = pq_create(3);
    assert_true(pq_push(queue_handle, NULL, 1));
    assert_true(pq_push(queue_handle, NULL, 2));
    assert_int_equal(pq_size(queue_handle), 2);
    pq_destroy(queue_handle, NULL);
}

static void test_push_pop_priority(void **state) {
    priority_queue_t *queue_handle = pq_create(10);
    void *extracted_data;
    int extracted_priority;

    pq_push(queue_handle, (void *)1, 10);
    pq_push(queue_handle, (void *)2, 30);
    pq_push(queue_handle, (void *)3, 20);

    assert_true(pq_pop(queue_handle, &extracted_data, &extracted_priority));
    assert_int_equal((intptr_t)extracted_data, 2);
    assert_int_equal(extracted_priority, 30);

    assert_true(pq_pop(queue_handle, &extracted_data, &extracted_priority));
    assert_int_equal((intptr_t)extracted_data, 3);
    assert_int_equal(extracted_priority, 20);

    assert_true(pq_pop(queue_handle, &extracted_data, &extracted_priority));
    assert_int_equal((intptr_t)extracted_data, 1);
    assert_int_equal(extracted_priority, 10);

    pq_destroy(queue_handle, NULL);
}

static void test_peek(void **state) {
    priority_queue_t *queue_handle = pq_create(10);
    void *extracted_data;
    int extracted_priority;

    pq_push(queue_handle, (void *)7, 100);
    assert_true(pq_peek(queue_handle, &extracted_data, &extracted_priority));
    assert_int_equal((intptr_t)extracted_data, 7);
    assert_int_equal(extracted_priority, 100);
    assert_int_equal(pq_size(queue_handle), 1);

    pq_destroy(queue_handle, NULL);
}

static void test_overflow(void **state) {
    priority_queue_t *queue_handle = pq_create(2);

    assert_true(pq_push(queue_handle, NULL, 1));
    assert_true(pq_push(queue_handle, NULL, 2));
    assert_false(pq_push(queue_handle, NULL, 3));

    pq_destroy(queue_handle, NULL);
}

static void test_clear(void **state) {
    priority_queue_t *queue_handle = pq_create(5);
    int *first_item = make_int(1);
    int *second_item = make_int(2);

    free_counter = 0;
    pq_push(queue_handle, first_item, 1);
    pq_push(queue_handle, second_item, 2);
    pq_clear(queue_handle, free_item);

    assert_true(pq_is_empty(queue_handle));
    assert_int_equal(free_counter, 2);

    pq_destroy(queue_handle, NULL);
}

static void test_empty_operations(void **state) {
    priority_queue_t *queue_handle = pq_create(3);
    assert_false(pq_pop(queue_handle, NULL, NULL));
    assert_false(pq_peek(queue_handle, NULL, NULL));
    pq_destroy(queue_handle, NULL);
}

static void test_equal_priorities(void **state) {
    priority_queue_t *queue_handle = pq_create(5);
    int first_priority, second_priority;

    pq_push(queue_handle, (void *)1, 10);
    pq_push(queue_handle, (void *)2, 10);

    assert_true(pq_pop(queue_handle, NULL, &first_priority));
    assert_true(pq_pop(queue_handle, NULL, &second_priority));
    assert_int_equal(first_priority, 10);
    assert_int_equal(second_priority, 10);

    pq_destroy(queue_handle, NULL);
}

static void test_unlimited_queue(void **state) {
    priority_queue_t *queue_handle = pq_create(0);
    int extracted_priority;

    assert_true(pq_push(queue_handle, NULL, 1));
    assert_true(pq_push(queue_handle, NULL, 5));
    assert_true(pq_push(queue_handle, NULL, 3));
    assert_int_equal(pq_size(queue_handle), 3);

    assert_true(pq_pop(queue_handle, NULL, &extracted_priority));
    assert_int_equal(extracted_priority, 5);

    pq_destroy(queue_handle, NULL);
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
    priority_queue_t *queue_handle = pq_create(3);
    pq_push(queue_handle, (void *)1, 1);
    pq_push(queue_handle, (void *)2, 2);
    pq_clear(queue_handle, NULL);
    assert_true(pq_is_empty(queue_handle));
    pq_destroy(queue_handle, NULL);
}

static void test_pop_peek_null_params(void **state) {
    priority_queue_t *queue_handle = pq_create(2);
    pq_push(queue_handle, (void *)1, 5);
    assert_true(pq_peek(queue_handle, NULL, NULL));
    assert_true(pq_pop(queue_handle, NULL, NULL));
    pq_destroy(queue_handle, NULL);
}

static void test_pop_only_data(void **state) {
    priority_queue_t *queue_handle = pq_create(2);
    void *extracted_data;

    pq_push(queue_handle, (void *)123, 9);
    assert_true(pq_pop(queue_handle, &extracted_data, NULL));
    assert_int_equal((intptr_t)extracted_data, 123);

    pq_destroy(queue_handle, NULL);
}

static void test_pop_only_priority(void **state) {
    priority_queue_t *queue_handle = pq_create(2);
    int extracted_priority;

    pq_push(queue_handle, (void *)123, 9);
    assert_true(pq_pop(queue_handle, NULL, &extracted_priority));
    assert_int_equal(extracted_priority, 9);

    pq_destroy(queue_handle, NULL);
}

static void test_peek_only_data(void **state) {
    priority_queue_t *queue_handle = pq_create(2);
    void *extracted_data;

    pq_push(queue_handle, (void *)55, 4);
    assert_true(pq_peek(queue_handle, &extracted_data, NULL));
    assert_int_equal((intptr_t)extracted_data, 55);

    pq_destroy(queue_handle, NULL);
}

static void test_peek_only_priority(void **state) {
    priority_queue_t *queue_handle = pq_create(2);
    int extracted_priority;

    pq_push(queue_handle, (void *)55, 4);
    assert_true(pq_peek(queue_handle, NULL, &extracted_priority));
    assert_int_equal(extracted_priority, 4);

    pq_destroy(queue_handle, NULL);
}

static void test_heapify_up_single_element(void **state) {
    priority_queue_t *queue_handle = pq_create(1);
    int extracted_priority;

    pq_push(queue_handle, NULL, 42);
    assert_true(pq_peek(queue_handle, NULL, &extracted_priority));
    assert_int_equal(extracted_priority, 42);

    pq_destroy(queue_handle, NULL);
}

static void test_heapify_down_single_element(void **state) {
    priority_queue_t *queue_handle = pq_create(2);
    int extracted_priority;

    pq_push(queue_handle, NULL, 10);
    pq_push(queue_handle, NULL, 5);
    pq_pop(queue_handle, NULL, NULL);
    assert_true(pq_peek(queue_handle, NULL, &extracted_priority));
    assert_int_equal(extracted_priority, 5);

    pq_destroy(queue_handle, NULL);
}

static void test_destroy_no_free(void **state) {
    priority_queue_t *queue_handle = pq_create(2);
    pq_push(queue_handle, (void *)1, 1);
    pq_destroy(queue_handle, NULL);
}

static void test_destroy_frees_queue(void **state) {
    priority_queue_t *queue_handle = pq_create(3);
    int *first_item = make_int(1);
    int *second_item = make_int(2);

    free_counter = 0;
    pq_push(queue_handle, first_item, 1);
    pq_push(queue_handle, second_item, 2);
    pq_destroy(queue_handle, free_item);

    assert_int_equal(free_counter, 2);
}

static void test_clear_resets_capacity(void **state) {
    priority_queue_t *queue_handle = pq_create(2);

    pq_push(queue_handle, NULL, 1);
    pq_push(queue_handle, NULL, 2);
    pq_clear(queue_handle, NULL);

    assert_true(pq_is_empty(queue_handle));
    assert_false(pq_is_full(queue_handle));
    assert_true(pq_push(queue_handle, NULL, 3));

    pq_destroy(queue_handle, NULL);
}

static void test_pop_clears_last_element(void **state) {
    priority_queue_t *queue_handle = pq_create(1);

    pq_push(queue_handle, NULL, 7);
    assert_true(pq_pop(queue_handle, NULL, NULL));
    assert_true(pq_is_empty(queue_handle));

    pq_destroy(queue_handle, NULL);
}

static void test_heap_stability_up(void **state) {
    priority_queue_t *queue_handle = pq_create(10);
    int extracted_priority;

    pq_push(queue_handle, NULL, 1);
    pq_push(queue_handle, NULL, 2);
    pq_push(queue_handle, NULL, 3);
    pq_push(queue_handle, NULL, 4);

    assert_true(pq_peek(queue_handle, NULL, &extracted_priority));
    assert_int_equal(extracted_priority, 4);

    pq_destroy(queue_handle, NULL);
}

static void test_heap_stability_down(void **state) {
    priority_queue_t *queue_handle = pq_create(10);
    int extracted_priority;

    pq_push(queue_handle, NULL, 10);
    pq_push(queue_handle, NULL, 7);
    pq_push(queue_handle, NULL, 8);
    pq_pop(queue_handle, NULL, NULL);

    assert_true(pq_peek(queue_handle, NULL, &extracted_priority));
    assert_int_equal(extracted_priority, 8);

    pq_destroy(queue_handle, NULL);
}

static void test_unlimited_queue_realloc(void **state) {
    priority_queue_t *queue_handle = pq_create(0);
    int extracted_priority;
    int index;

    for (index = 0; index < 100; index++) {
        assert_true(pq_push(queue_handle, NULL, index));
    }

    assert_int_equal(pq_size(queue_handle), 100);
    assert_true(pq_pop(queue_handle, NULL, &extracted_priority));
    assert_int_equal(extracted_priority, 99);

    pq_destroy(queue_handle, NULL);
}

static void test_push_checks_overflow(void **state) {
    priority_queue_t *queue_handle = pq_create(1);

    assert_true(pq_push(queue_handle, NULL, 1));
    assert_false(pq_push(queue_handle, NULL, 2));

    pq_destroy(queue_handle, NULL);
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