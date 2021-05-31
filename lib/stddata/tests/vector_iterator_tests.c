#include <vector_iterator.h>
#include <vector.h>

void EmptyVectorBeginEnd() {
    Vector vector = NewEmptyVector();
    assert(VectorIteratorCompare(VectorBegin(vector), VectorEnd(vector)) == 0);
    DeleteVector(vector);
}

void NonEmptyVectorBegin() {
    int x = 2;
    Vector vector = NewFilledVector(1, (void*[]){&x});
    assert(VectorIteratorGet(VectorBegin(vector)) == &x);
    DeleteVector(vector);
}

void VectorIterating() {
    const int nitems = 5;
    int items[] = {123, 234, 62, 123, 7};
    void* pointers[nitems];
    for(int i = 0; i < nitems; i++) {
        pointers[i] = &items[i];
    }
    Vector vector = NewFilledVector(nitems, pointers);
    int i = 0;
    for(VectorIterator iter = VectorBegin(vector); 
        VectorIteratorLess(iter, VectorEnd(vector)); 
        VectorIteratorIncr(&iter)) {
        assert(VectorIteratorGet(iter) == &items[i++]);
    }
    DeleteVector(vector);
}

void VectorFor() {
    const int nitems = 5;
    int items[] = {123, 234, 62, 123, 7};
    Vector vec = NewVector(nitems);
    int i = 0;
    VECTORFOR(vec, iterator) {
        VectorIteratorSet(iterator, &items[i++]);
    }

    i = 0;
    VECTORFOR(vec, iterator) {
        assert(VectorIteratorGet(iterator) == &items[i++]);
    }
    DeleteVector(vec);
}

void VectorIteratorIncrDecr() {
    const int nsizes = 5;
    int sizes[] = {12, 123, 54, 754, 1};
    for(int i = 0; i < nsizes; i++) {
        Vector vector = NewEmptyVector();
        VectorIterator iter = VectorBegin(vector);
        for(int j = 0; j < sizes[i]; j++) {
            VectorIteratorIncr(&iter);
        }
        for(int j = 0; j < sizes[i]; j++) {
            VectorIteratorDecr(&iter);
        }
        assert(VectorIteratorCompare(iter, VectorBegin(vector)) == 0);
    }
}

void VectorIteratorTests() {
    EmptyVectorBeginEnd();
    NonEmptyVectorBegin();
    VectorIterating();
    VectorFor();
}
