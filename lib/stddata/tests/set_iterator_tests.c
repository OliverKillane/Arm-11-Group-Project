#include <set_iterator.h>
#include <set.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
unsigned long long SetIteratorHashFunction(void* item) {
    return (unsigned long long)item;
}
#pragma GCC diagnostic pop

bool SetIteratorEqFunction(void* a, void* b) {
    return a == b;
}

void EmptySetBeginEnd() {
    Set set = NewEmptySet(SetIteratorHashFunction, SetIteratorEqFunction);
    assert(SetIteratorCompare(SetBegin(set), SetEnd(set)) == 0);
    DeleteSet(set);
}

void NonEmptySetBegin() {
    int x = 2;
    Set set = NewFilledSet(SetIteratorHashFunction, SetIteratorEqFunction, 1, (void*[]){&x});
    assert(SetIteratorGet(SetBegin(set)) == &x);
    DeleteSet(set);
}

int SetSortComp(const void* a, const void* b) {
    return (*(void**)a > *(void**)b) - (*(void**)b > *(void**)a);
}

void SetIterating() {
    int nitems = 1e1;
    int items[nitems];
    void* pointers[nitems];
    for(int i = 0; i < nitems; i++) {
        pointers[i] = &items[i];
    }
    Set set = NewFilledSet(SetIteratorHashFunction, SetIteratorEqFunction, nitems, pointers);

    int i = 0;
    void* found[nitems];
    for(SetIterator iter = SetBegin(set); 
        SetIteratorLess(iter, SetEnd(set)); 
        SetIteratorIncr(&iter)) {
        found[i++] = SetIteratorGet(iter);
    }
    assert(i == nitems);
    qsort(found, nitems, sizeof(void*), SetSortComp);
    for(int i = 0; i < nitems; i++) {
        assert(found[i] == pointers[i]);
    }
    DeleteSet(set);
}

void SetFor() {
    int nitems = 1e3;
    int items[nitems];
    void* pointers[nitems];
    for(int i = 0; i < nitems; i++) {
        pointers[i] = &items[i];
    }
    Set set = NewFilledSet(SetIteratorHashFunction, SetIteratorEqFunction, nitems, pointers);

    int i = 0;
    void* found[nitems];
    SETFOR(set, iter) {
        found[i++] = SetIteratorGet(iter);
    }
    assert(i == nitems);
    qsort(found, nitems, sizeof(void*), SetSortComp);
    for(int i = 0; i < nitems; i++) {
        assert(found[i] == pointers[i]);
    }
    DeleteSet(set);
}

void SetIteratorTests() {
    EmptySetBeginEnd();
    NonEmptySetBegin();
    SetIterating();
    SetFor();
}