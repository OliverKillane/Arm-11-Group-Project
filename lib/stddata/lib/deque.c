#include <list.h>
#include <deque.h>

Deque NewDeque() {
    return NewEmptyList();
}

void DeleteDeque(Deque restrict deque) {
    DeleteList(deque);
}

void DequePushFront(Deque restrict deque, void* new_item) {
    ListPushFront(deque, new_item);
}

void DequePushBack(Deque restrict deque, void* new_item) {
    ListPushBack(deque, new_item);
}

void* DequePopFront(Deque restrict deque) {
    return ListPopFront(deque);
}

void* DequePopBack(Deque restrict deque) {
    return ListPopBack(deque);
}

void* DequePeekFront(Deque restrict deque) {
    return ListFront(deque);
}

void* DequePeekBack(Deque restrict deque) {
    return ListBack(deque);
}

int DequeSize(Deque restrict deque) {
    return ListSize(deque);
}

bool DequeEmpty(Deque restrict deque) {
    return ListEmpty(deque);
}