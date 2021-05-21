#include <vector.h>
#include <assert.h>

void EmptyVectorIsEmpty() {
    Vector vector = NewEmptyVector();
    assert(VectorEmpty(vector));
    DeleteVector(vector);
}

void NewVectorRequestedSize() {
    const int nchecks = 4;
    int sizes[] = {6, 10, 120, 5324};
    for(int i = 0; i < nchecks; i++) {
        Vector vector = NewVector(sizes[i]);
        assert(VectorSize(vector) == sizes[i]);
        DeleteVector(vector);
    }
}

void VectorAddingElementsUsingPushBack() {
    const int nitems = 5;
    int items[] = {6, 2, 4, 10, 7};
    Vector vector = NewEmptyVector();
    for(int i = 0; i < nitems; i++) {
        VectorPushBack(vector, &items[i]);
    }
    for(int i = 0; i < nitems; i++) {
        assert(VectorGet(vector, i) == &items[i]);
    }
    DeleteVector(vector);
}

void VectorAddingElementsUsingSet() {
    const int nitems = 5;
    int items[] = {6, 2, 4, 10, 7};
    Vector vector = NewVector(nitems);
    for(int i = 0; i < nitems; i++) {
        VectorSet(vector, i, &items[i]);
    }
    for(int i = 0; i < nitems; i++) {
        assert(VectorGet(vector, i) == &items[i]);
    }
    DeleteVector(vector);
}

void VectorRequestedResize() {
    const int nchecks = 5;
    int oldsizes[] = {10, 20, 50, 5678, 2316};
    int newsizes[] = {5, 654, 1, 67890, 2};
    for(int i = 0; i < nchecks; i++) {
        Vector vector = NewVector(oldsizes[i]);
        VectorResize(vector, newsizes[i]);
        assert(VectorSize(vector) == newsizes[i]);
        DeleteVector(vector);
    }
}

void VectorRequestedForcedResize() {
    const int nchecks = 5;
    int oldsizes[] = {10, 20, 50, 5678, 2316};
    int newsizes[] = {5, 654, 1, 67890, 2};
    for(int i = 0; i < nchecks; i++) {
        Vector vector = NewVector(oldsizes[i]);
        VectorForcedResize(vector, MIN_VECTOR_SIZE + newsizes[i]);
        assert(VectorAllocSize(vector) == MIN_VECTOR_SIZE + newsizes[i]);
        DeleteVector(vector);
    }
}

void VectorRequestedClear() {
    const int nchecks = 5;
    int sizes[] = {10, 20, 50, 5678, 2316};
    for(int i = 0; i < nchecks; i++) {
        Vector vector = NewVector(sizes[i]);
        VectorClear(vector);
        assert(VectorSize(vector) == 0);
        DeleteVector(vector);
    }
}

void VectorPoppingBack() {
    const int nitems = 5;
    const int nremoved = 3;
    int items[] = {453, 12, 4, 65, 7};
    Vector vector = NewEmptyVector();
    for(int i = 0; i < nitems; i++) {
        VectorPushBack(vector, &items[i]);
    }
    for(int i = 0 ; i < nremoved; i++) {
        assert(VectorPopBack(vector) == &items[nitems - i - 1]);
    }
    for(int i = 0; i < nitems - nremoved; i++) {
        assert(VectorGet(vector, i) == &items[i]);
    }
    DeleteVector(vector);
}

void VectorFilled() {
    const int nitems = 5;
    int items[] = {123, 234, 62, 123, 7};
    void* pointers[nitems];
    for(int i = 0; i < nitems; i++) {
        pointers[i] = &items[i];
    }
    Vector vector = NewFilledVector(nitems, pointers);
    for(int i = 0; i < nitems; i++) {
        assert(VectorGet(vector, i) == &items[i]);
    }
    DeleteVector(vector);
}

void VectorTests() {
    EmptyVectorIsEmpty();
    NewVectorRequestedSize();
    VectorAddingElementsUsingPushBack();
    VectorAddingElementsUsingSet();
    VectorRequestedResize();
    VectorRequestedForcedResize();
    VectorRequestedClear();
    VectorPoppingBack();
}