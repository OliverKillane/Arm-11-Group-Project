#include <list_iterator.h>
#include <list.h>
#include <assert.h>

void EmptyListBeginEnd() {
    List list = NewEmptyList();
    assert(ListIteratorEqual(ListBegin(list), ListEnd(list)));
    DeleteList(list);
}

void NonEmptyListBegin() {
    int x = 2;
    List list = NewFilledList(1, (void*[]){&x});
    assert(ListIteratorGet(ListBegin(list)) == &x);
    DeleteList(list);
}

void ListIterating() {
    const int nitems = 5;
    int items[] = {123, 234, 62, 123, 7};
    void* pointers[nitems];
    for(int i = 0; i < nitems; i++) {
        pointers[i] = &items[i];
    }
    List list = NewFilledList(nitems, pointers);
    int i = 0;
    for(ListIterator iter = ListBegin(list); 
        !ListIteratorEqual(iter, ListEnd(list)); 
        ListIteratorIncr(&iter)) {
        assert(ListIteratorGet(iter) == &items[i++]);
    }
    DeleteList(list);
}

void ListFor() {
    const int nitems = 5;
    int items[] = {123, 234, 62, 123, 7};
    List vec = NewList(nitems);
    int i = 0;
    LISTFOR(vec, iterator) {
        ListIteratorSet(iterator, &items[i++]);
    }

    i = 0;
    LISTFOR(vec, iterator) {
        assert(ListIteratorGet(iterator) == &items[i++]);
    }
    DeleteList(vec);
}

void ListInsertAfterBeforeRemove() {
    int nchecks = 2;
    int nafter[] = {12, 20, 132, 542, 123};
    int nbefore[] = {7, 12454, 654, 12, 6};
    int a = 4;
    int b = 6;
    for(int i = 0; i < nchecks; i++) {
        List list = NewEmptyList();
        ListIterator iter = ListBegin(list);
        for(int j = 0; j < nafter[i]; j++) {
            ListIteratorInsertAfter(iter, &a);
        }
        for(int j = 0; j < nbefore[i]; j++) {
            ListIteratorInsertBefore(iter, &b);
        }
        iter = ListBegin(list);
        for(int j = 0; j < nbefore[i]; j++) {
            assert(ListIteratorGet(iter) == &b);
            ListIteratorIncr(&iter);
        }
        for(int j = 0; j < nafter[i]; j++) {
            assert(ListIteratorGet(iter) == &a);
            ListIteratorIncr(&iter);
        }
        assert(ListIteratorEqual(iter, ListEnd(list)));
        assert(ListSize(list) == nafter[i] + nbefore[i]);
        iter = ListBegin(list);
        for(int j = 0; j < nbefore[i]; j++) {
            ListIteratorRemove(&iter);
        }
        LISTFOR(list, iter2) {
            assert(ListIteratorGet(iter2) == &a);
        }
        assert(ListSize(list) == nafter[i]);
        assert(ListIteratorEqual(iter, ListBegin(list)));
        DeleteList(list);
    }
}

void ListIteratorTests() {
    EmptyListBeginEnd();
    NonEmptyListBegin();
    ListIterating();
    ListFor();
    ListInsertAfterBeforeRemove();
}