#include <decision_tree.h>
#include <map.h>
#include <vector.h>
#include <list.h>
#include <map_iterator.h>
#include <vector_iterator.h>
#include <list_iterator.h>
#include <stdlib.h>
#include <stdbool.h>

/* Interface Definitions */

DecisionTree NewEmptyDecisionTree(
    unsigned long long(*hash_func)(void*), 
    bool (*eq_func)(void*, void*)
) {
    DecisionTree out = malloc(sizeof(DecisionTreeRepr));
    out -> next = NewEmptyMap(hash_func, eq_func);
    out -> value = NULL;
    out -> size = 0;
    return out;
}

void DeleteDecisionTree(DecisionTree restrict tree) {
    MAPFOR(tree->next, iter) {
        DeleteDecisionTree(MapIteratorGet(iter).value);
    }
    DeleteMap(tree->next);
    free(tree);
}

int DecisionTreeSize(DecisionTree restrict tree) {
    return tree -> size;
}

bool DecisionTreeEmpty(DecisionTree restrict tree) {
    return DecisionTreeSize(tree) == 0;
}

void DecisionTreeInsertVector(DecisionTree tree, Vector restrict data, void* value) {
    DecisionTree root = tree;
    root->size++;
    VECTORFOR(data, iter) {
        DecisionTree nextTree = MapGet(tree->next, VectorIteratorGet(iter));
        if(nextTree == NULL) {
            nextTree = NewEmptyDecisionTree(tree->next->hash_func, tree->next->eq_func);
            MapSet(tree->next, VectorIteratorGet(iter), nextTree);
        }
        tree = nextTree;
    }
    if(tree->value != NULL) {
        root->size--;
    }
    tree->value = value;
}

void DecisionTreeInsertList(DecisionTree tree, List restrict data, void* value) {
    DecisionTree root = tree;
    root->size++;
    LISTFOR(data, iter) {
        DecisionTree nextTree = MapGet(tree->next, ListIteratorGet(iter));
        if(nextTree == NULL) {
            nextTree = NewEmptyDecisionTree(tree->next->hash_func, tree->next->eq_func);
            MapSet(tree->next, ListIteratorGet(iter), nextTree);
        }
        tree = nextTree;
    }
    if(tree->value != NULL) {
        root->size--;
    }
    tree->value = value;
}

void* DecisionTreeQueryVector(DecisionTree restrict tree, Vector restrict data) {
    VECTORFOR(data, iter) {
        DecisionTree nextTree = MapGet(tree->next, VectorIteratorGet(iter));
        if(nextTree == NULL) {
            return NULL;
        }
        tree = nextTree;
    }
    return tree -> value;
}

void* DecisionTreeQueryList(DecisionTree restrict tree, List restrict data) {
    LISTFOR(data, iter) {
        DecisionTree nextTree = MapGet(tree->next, ListIteratorGet(iter));
        if(nextTree == NULL) {
            return NULL;
        }
        tree = nextTree;
    }
    return tree -> value;
}
