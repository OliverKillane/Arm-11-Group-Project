#include <deque.h>
#include <assert.h>

void EmptyDequeIsEmpty() {
    Deque deque = NewDeque();
    assert(DequeEmpty(deque));
    DeleteDeque(deque);
}

void DequePushPop() {
    int nitems = 1e4;
    int items[nitems];
    Deque deque = NewDeque();
    for(int i = 0; i < nitems; i++) {
        DequePushBack(deque, &items[i]);
    }
    assert(DequeSize(deque) == nitems);
    for(int i = 0; i < nitems; i++) {
        assert(DequePopFront(deque) == &items[i]);
    }
    assert(DequeEmpty(deque));
    for(int i = 0; i < nitems; i++) {
        DequePushFront(deque, &items[i]);
    }
    assert(DequeSize(deque) == nitems);
    for(int i = 0; i < nitems; i++) {
        assert(DequePopBack(deque) == &items[i]);
    }
    assert(DequeEmpty(deque));
    DeleteDeque(deque);
}

void DequeTests() {
    EmptyDequeIsEmpty();
    DequePushPop();
}
