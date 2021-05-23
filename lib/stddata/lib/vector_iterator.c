#include <stdio.h>
#include <assert.h>
#include <vector.h>
#include <vector_iterator.h>

VectorIterator VectorBegin(Vector restrict vector) {
    return (VectorIterator){
        vector,
        0
    };
}

VectorIterator VectorEnd(Vector restrict vector) {
    return (VectorIterator){
        vector,
        VectorSize(vector)
    };
}

bool VectorIteratorLess(VectorIterator a, VectorIterator b) {
    assert(a.vector == b.vector);
    return a.itemNum < b.itemNum;
}

int VectorIteratorCompare(VectorIterator a, VectorIterator b) {
    return VectorIteratorLess(b, a) - VectorIteratorLess(a, b);
}

void VectorIteratorIncr(VectorIterator * restrict iter) {
    iter->itemNum++;
}

void VectorIteratorDecr(VectorIterator * restrict iter) {
    iter->itemNum--;
}

void* VectorIteratorGet(VectorIterator iter) {
    return VectorGet(iter.vector, iter.itemNum);
}

void VectorIteratorSet(VectorIterator iter, void* new_item) {
    VectorSet(iter.vector, iter.itemNum, new_item);
}