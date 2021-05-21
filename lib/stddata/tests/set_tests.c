#include <set.h>
#include <assert.h>
#include <stdlib.h>

/* Helper Functions */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
unsigned long long SetHashFunction(void* item) {
    return 0;
}
#pragma GCC diagnostic pop

bool SetEqFunction(void* a, void* b) {
    return a == b;
}

/* Tests */
void EmptySetIsEmpty() {
    Set set = NewEmptySet(SetHashFunction, SetEqFunction);
    assert(SetEmpty(set));
    DeleteSet(set);
}

void SetAddingItems() {
    int nItems = 1e3;
    int *items = malloc(sizeof(int) * nItems);
    Set set = NewEmptySet(SetHashFunction, SetEqFunction);
    for(int i = 0; i < nItems; i++) {
        SetInsert(set, &items[i]);
    }
    for(int i = 0; i < nItems; i++) {
        assert(SetQuery(set, &items[i]));
    }
    int *nonitems = malloc(sizeof(int) * nItems);
    for(int i = 0; i < nItems; i++) {
        assert(!SetQuery(set, &nonitems[i]));
    }
    DeleteSet(set);
    free(items);
    free(nonitems);
}

void SetRemovingItems() {
    int nItems = 1e3;
    int items[nItems];
    void *pointers[nItems];
    for(int i = 0; i < nItems; i++) {
        pointers[i] = &items[i];
    }
    Set set = NewFilledSet(SetHashFunction, SetEqFunction, nItems, pointers);
    for(int i = 0; i < nItems; i++) {
        assert(SetQuery(set, &items[i]));
    }
    int nRemoved = 1e2;
    for(int i = 0; i < nRemoved; i++) {
        SetRemove(set, &items[i]);
    }
    for(int i = 0; i < nRemoved; i++) {
        SetRemove(set, &items[i]);
    }
    for(int i = 0; i < nItems; i++) {
        assert(SetQuery(set, &items[i]) == (i >= nRemoved));
    }
    DeleteSet(set);

}

void SetTests() {
    EmptySetIsEmpty();
    SetAddingItems();
    SetRemovingItems();
}