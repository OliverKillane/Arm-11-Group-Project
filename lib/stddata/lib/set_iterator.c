#include <stdlib.h>
#include <set_iterator.h>
#include <set.h>
#include <stdbool.h>

SetIterator SetBegin(Set set) {
    if(SetSize(set) == 0) {
        return (SetIterator) {
            set,
            -1
        };
    }
    int index = set->min_index;

    while(set->data[index] == NULL || set->data[index] == SET_SENTINEL) {
        index++;
    }

    return (SetIterator){
        set,
        index
    };
}

SetIterator SetEnd(Set set) {
    return (SetIterator){
        set,
        -1
    };
}

bool SetIteratorLess(SetIterator a, SetIterator b) {
    assert(a.set == b.set);
    if(a.index == -1) {
        return false;
    }
    if(b.index == -1) {
        return true;
    }
    return a.index < b.index;
}

int SetIteratorCompare(SetIterator a, SetIterator b) {
    return SetIteratorLess(b, a) - SetIteratorLess(a, b);
}

void SetIteratorIncr(SetIterator *iter) {
    assert(iter->index != -1);
    
    do {
        iter->index++;
    } while((iter->set->data[iter->index] == NULL || iter->set->data[iter->index] == SET_SENTINEL) 
            && iter->index <= iter->set->max_index);

    if(iter->index > iter->set->max_index) {
        iter->index = -1;
        return;
    }
}

void SetIteratorDecr(SetIterator *iter) {
    if(iter->index == -1) {
        iter->index = iter->set->max_index + 1;
    }

    do {
        iter->index--;
        assert(iter->index >= iter->set->min_index);
    } while(iter->set->data[iter->index] == NULL || iter->set->data[iter->index] == SET_SENTINEL);
}

void* SetIteratorGet(SetIterator iter) {
    return iter.set->data[iter.index];
}