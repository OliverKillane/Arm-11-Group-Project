#include <list.h>
#include <assert.h>

void EmptyListIsEmpty() {
    List list = NewEmptyList();
    assert(ListEmpty(list));
    DeleteList(list);
}

void ListSizes() {
    int nsizes = 5;
    int sizes[] = {124, 346, 2, 1421, 11};
    for(int i = 0; i < nsizes; i++) {
        List list = NewList(sizes[i]);
        assert(ListSize(list) == sizes[i]);
        DeleteList(list);
    }
}

void ListPushPop() {
    int nitems = 5;
    int items[] = {213, 214, 665, 76, 87};
    List list = NewEmptyList();
    for(int i = 0; i < nitems; i++) {
        ListPushBack(list, &items[i]);
    }
    for(int i = 0; i < nitems; i++) {
        assert(ListPopFront(list) == &items[i]);
    }
    for(int i = 0; i < nitems; i++) {
        ListPushFront(list, &items[i]);
    }
    for(int i = 0; i < nitems; i++) {
        assert(ListPopBack(list) == &items[i]);
    }
    DeleteList(list);
}

void ListSetGet() {
    int nitems = 6;
    int items[] = {123, 356, 32, 7654, 76547};
    List list = NewList(nitems);
    for(int i = 0; i < nitems; i++) {
        ListSet(list, i, &items[i]);
    }
    for(int i = 0; i < nitems; i++) {
        assert(ListGet(list, i) == &items[i]);
    }
    DeleteList(list);
}

void ListFilled() {
    const int nitems = 5;
    int items[] = {123, 234, 62, 123, 7};
    void* pointers[nitems];
    for(int i = 0; i < nitems; i++) {
        pointers[i] = &items[i];
    }
    List list = NewFilledList(nitems, pointers);
    for(int i = 0; i < nitems; i++) {
        assert(ListPopFront(list) == &items[i]);
    }
    DeleteList(list);
}

void ListTests() {
    EmptyListIsEmpty();
    ListSizes();
    ListPushPop();
    ListSetGet();
}