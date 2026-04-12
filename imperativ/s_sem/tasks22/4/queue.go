package main

// #cgo CFLAGS: -I.
// #cgo LDFLAGS: -L. -lqueue
// #include "queue.h"
import "C"
import (
	"errors"
	"fmt"
)

type Queue struct {
	ptr *C.queue_t
}

func NewQueue() (*Queue, error) {
	ptr := C.queue_new()
	if ptr == nil {
		return nil, errors.New("failed to create queue")
	}
	return &Queue{ptr: ptr}, nil
}

func (q *Queue) Push(value int) error {
	if q.ptr == nil {
		return errors.New("queue is closed")
	}
	ok := C.queue_push(q.ptr, C.int(value))
	if !ok {
		return errors.New("failed to push value")
	}
	return nil
}

func (q *Queue) Pop() (int, error) {
	if q.ptr == nil {
		return 0, errors.New("queue is closed")
	}
	var value C.int
	ok := C.queue_pop(q.ptr, &value)
	if !ok {
		return 0, errors.New("queue is empty")
	}
	return int(value), nil
}

func (q *Queue) Peek() (int, error) {
	if q.ptr == nil {
		return 0, errors.New("queue is closed")
	}
	var value C.int
	ok := C.queue_peek(q.ptr, &value)
	if !ok {
		return 0, errors.New("queue is empty")
	}
	return int(value), nil
}

func (q *Queue) IsEmpty() bool {
	if q.ptr == nil {
		return true
	}
	return bool(C.queue_is_empty(q.ptr))
}

func (q *Queue) Size() int {
	if q.ptr == nil {
		return 0
	}
	return int(C.queue_size(q.ptr))
}

func (q *Queue) Clear() {
	if q.ptr != nil {
		C.queue_clear(q.ptr)
	}
}

func (q *Queue) Close() error {
	if q.ptr != nil {
		C.queue_free(q.ptr)
		q.ptr = nil
	}
	return nil
}

func (q *Queue) String() string {
	if q.ptr == nil {
		return "<closed>"
	}

	tempQ, _ := NewQueue()
	defer tempQ.Close()

	values := make([]int, 0, q.Size())
	for !q.IsEmpty() {
		val, err := q.Pop()
		if err != nil {
			break
		}
		values = append(values, val)
		tempQ.Push(val)
	}

	for !tempQ.IsEmpty() {
		val, _ := tempQ.Pop()
		q.Push(val)
	}

	if len(values) == 0 {
		return "[]"
	}
	result := "["
	for i, v := range values {
		if i > 0 {
			result += ", "
		}
		result += fmt.Sprintf("%d", v)
	}
	result += "]"
	return result
}
