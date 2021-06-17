#include <decision_tree.h>
#include <vector.h>
#include <list.h>
#include <vector_iterator.h>
#include <list_iterator.h>
#include <assert.h>
#include <stdlib.h>

/* Helper Functions */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
unsigned long long DecisionTreeHashFunction(void* item) {
    return item;
}
#pragma GCC diagnostic pop

bool DecisionTreeEqFunction(void* a, void* b) {
    return a == b;
}

/* Tests */
void EmptyDecisionTreeIsEmpty() {
    DecisionTree tree = NewEmptyDecisionTree(DecisionTreeHashFunction, DecisionTreeEqFunction);
    assert(DecisionTreeEmpty(tree));
    DeleteDecisionTree(tree);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-conversion"
void DecisionTreeAddingSequencesVector() {
    int sequences_count = 10;
    Vector sequences[] = {
        NewFilledVector(5, (void*[]){2, 2, 2, 2, 2}),
        NewFilledVector(5, (void*[]){2, 8, 2, 2, 2}),
        NewFilledVector(5, (void*[]){2, 8, 8, 2, 2}),
        NewFilledVector(5, (void*[]){2, 2, 2, 2, 8}),
        NewFilledVector(5, (void*[]){2, 8, 2, 8, 2}),
        NewFilledVector(5, (void*[]){8, 2, 2, 2, 2}),
        NewFilledVector(5, (void*[]){8, 8, 2, 2, 2}),
        NewFilledVector(5, (void*[]){8, 8, 8, 2, 2}),
        NewFilledVector(5, (void*[]){8, 2, 2, 2, 8}),
        NewFilledVector(5, (void*[]){8, 8, 2, 8, 2}),
    };
    void* values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    DecisionTree tree = NewEmptyDecisionTree(DecisionTreeHashFunction, DecisionTreeEqFunction);
    for(int i = 0; i < sequences_count; i++) {
        assert(DecisionTreeQuery(tree, sequences[i]) == NULL);
    }
    for(int i = 0; i < sequences_count; i++) {
        DecisionTreeInsert(tree, sequences[i], values[i]);
    }
    for(int i = 0; i < sequences_count; i++) {
        DecisionTreeInsert(tree, sequences[i], values[i]);
    }
    for(int i = 0; i < sequences_count; i++) {
        assert(DecisionTreeQuery(tree, sequences[i]) == values[i]);
    }
    assert(DecisionTreeSize(tree) == sequences_count);
    DeleteDecisionTree(tree);
    for(int i = 0; i < sequences_count; i++) {
        DeleteVector(sequences[i]);
    }
}

void DecisionTreeAddingSequencesList() {
    int sequences_count = 10;
    List sequences[] = {
        NewFilledList(5, (void*[]){2, 2, 2, 2, 2}),
        NewFilledList(5, (void*[]){2, 8, 2, 2, 2}),
        NewFilledList(5, (void*[]){2, 8, 8, 2, 2}),
        NewFilledList(5, (void*[]){2, 2, 2, 2, 8}),
        NewFilledList(5, (void*[]){2, 8, 2, 8, 2}),
        NewFilledList(5, (void*[]){8, 2, 2, 2, 2}),
        NewFilledList(5, (void*[]){8, 8, 2, 2, 2}),
        NewFilledList(5, (void*[]){8, 8, 8, 2, 2}),
        NewFilledList(5, (void*[]){8, 2, 2, 2, 8}),
        NewFilledList(5, (void*[]){8, 8, 2, 8, 2}),
    };
    void* values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    DecisionTree tree = NewEmptyDecisionTree(DecisionTreeHashFunction, DecisionTreeEqFunction);
    for(int i = 0; i < sequences_count; i++) {
        assert(DecisionTreeQuery(tree, sequences[i]) == NULL);
    }
    for(int i = 0; i < sequences_count; i++) {
        DecisionTreeInsert(tree, sequences[i], values[i]);
    }
    for(int i = 0; i < sequences_count; i++) {
        DecisionTreeInsert(tree, sequences[i], values[i]);
    }
    for(int i = 0; i < sequences_count; i++) {
        assert(DecisionTreeQuery(tree, sequences[i]) == values[i]);
    }
    assert(DecisionTreeSize(tree) == sequences_count);
    DeleteDecisionTree(tree);
    for(int i = 0; i < sequences_count; i++) {
        DeleteList(sequences[i]);
    }
}
#pragma GCC diagnostic pop

void DecisionTreeTests() {
    EmptyDecisionTreeIsEmpty();
    DecisionTreeAddingSequencesVector();
}
