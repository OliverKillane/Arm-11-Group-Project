/**
 * @file decision_tree.h
 * @author Bartłomiej Cieślar
 * @brief @ref DecisionTree and utilities related to it
 */
#ifndef STDDATA_DECISION_TREE_H_
#define STDDATA_DECISION_TREE_H_

#include "map.h"
#include "vector.h"
#include "list.h"
#include <stdbool.h>

/**
 * @brief The structure representation of a decision tree
 * 
 * @note Do not use raw, always use via a @ref DecisionTree type
 * @warning Changing the internal variables manually outside of the interface functions will result
 *          in an undefined behaviour.
 */
typedef struct {
    Map next;
    void* value;
    int size;
} DecisionTreeRepr;

/**
 * @brief A decision tree
 * 
 * This is a decision tree, which works like a map for sequences of items:
 * It supports the following operations:
 *     - @ref DecisionTreeInsert Adds a sequence of items and the corresponding value
 *     - @ref DecisionTreeQuery Retreives the value of a sequence in the decision tree
 * 
 * It can be created using @ref NewEmptyDecisionTree and deallocated using @ref DeleteDecisionTree
 * To check its size and test if it is empty, use @ref DecisionTreeSize and @ref DecisionTreeEmpty
 * 
 * @note Even though this is only a typedef, do not delcare it as a pointer to @ref DecisionTreeRepr for
 *       improved code clarity
 */
typedef DecisionTreeRepr * DecisionTree;

/**
 * @brief Creates a new empty @ref DecisionTree
 * 
 * Dynamically allocates a new empty @ref DecisionTree using malloc.
 * 
 * @param hash_func The hash function for the items in the sequences
 * @param eq_func The equality function of the decision tree to compare the items in the sequences with
 * @warning In order to avoid memory leaks, please use 
 *          @ref DeleteDecisionTree to deallocate it once you are done using it.
 */
DecisionTree NewEmptyDecisionTree(
    unsigned long long(*hash_func)(void*), 
    bool (*eq_func)(void*, void*)
);

/**
 * @brief Deallocates a @ref DecisionTree
 *
 * @param tree The decision tree to be deallocated
 * @warning Trying to use or deallocate already deallocated @ref DecisionTree
 *          results in an undefined behaviour
 */
void DeleteDecisionTree(DecisionTree tree);

/**
 * @brief Returns the number of entries inside the decision tree
 * 
 * @param tree The decision tree to check the size of
 * @returns The size of the decision tree
 * @warning @p tree not being a valid allocated @ref DecisionTree results in an undefined behaviour
 */
int DecisionTreeSize(DecisionTree tree);

/**
 * @brief Checks if the decision tree has no entries
 * 
 * @param tree The decision tree to check the emptiness of
 * @returns @b true if the decision tree has no entries, otherwise @b false
 * @warning @p tree not being a valid allocated @ref DecisionTree results in an undefined behaviour
 */
bool DecisionTreeEmpty(DecisionTree tree);

/**
 * @brief Sets a value under a sequence represented by a vector to a new value
 * 
 * @param tree the decision tree to be modified
 * @param data the sequence to place the @p value under
 * @param value the value to be inserted into the decision tree
 * @note the @p value may be used to hold an integer value as well if it fits inside a void*
 * @warning @p data having an item of value 0 or 1 will result in an undefined behaviour
 * @warning @p tree not being a valid allocated @ref Map results in an undefined behaviour
 */
void DecisionTreeInsertVector(DecisionTree tree, Vector data, void* value);

/**
 * @brief Sets a value under a sequence represented by a list to a new value
 * 
 * @param tree the decision tree to be modified
 * @param data the sequence to place the @p value under
 * @param value the value to be inserted into the decision tree
 * @note the @p value may be used to hold an integer value as well if it fits inside a void*
 * @warning @p data having an item of value 0 or 1 will result in an undefined behaviour
 * @warning @p tree not being a valid allocated @ref Map results in an undefined behaviour
 */
void DecisionTreeInsertList(DecisionTree tree, List data, void* value);

/**
 * @brief Sets a value under a sequence to a new value
 * 
 * @param tree the decision tree to be modified
 * @param data the sequence to place the @p value under
 * @param value the value to be inserted into the decision tree
 * @note the @p value may be used to hold an integer value as well if it fits inside a void*
 * @warning @p data having an item of value 0 or 1 will result in an undefined behaviour
 * @warning @p tree not being a valid allocated @ref Map results in an undefined behaviour
 */
#define DecisionTreeInsert(tree, data, value) _Generic(data, \
                                       Vector: DecisionTreeInsertVector, \
                                       List: DecisionTreeInsertList\
)(tree, data, value)

/**
 * @brief Retreives a value under a sequence represented by a vector
 * 
 * @param tree the decision tree to retreive the value from
 * @param data the sequence to retreive value of
 * @returns the value of the sequence or NULL if the key is not assigned
 * @warning @p data having an item with a value 0 or 1 will result in an undefined behaviour
 * @warning @p tree not being a valid allocated @ref DecisionTree results in an undefined behaviour
 */
void* DecisionTreeQueryVector(DecisionTree tree, Vector data);

/**
 * @brief Retreives a value under a sequence represented by a list
 * 
 * @param tree the decision tree to retreive the value from
 * @param data the sequence to retreive value of
 * @returns the value of the sequence or NULL if the key is not assigned
 * @warning @p data having an item with a value 0 or 1 will result in an undefined behaviour
 * @warning @p tree not being a valid allocated @ref DecisionTree results in an undefined behaviour
 */
void* DecisionTreeQueryList(DecisionTree tree, List data);

/**
 * @brief Retreives a value under a sequence
 * 
 * @param tree the decision tree to retreive the value from
 * @param data the sequence to retreive value of
 * @returns the value of the sequence or NULL if the key is not assigned
 * @warning @p data having an item with a value 0 or 1 will result in an undefined behaviour
 * @warning @p tree not being a valid allocated @ref DecisionTree results in an undefined behaviour
 */
#define DecisionTreeQuery(tree, data) _Generic(data, \
                                       Vector: DecisionTreeQueryVector, \
                                       List: DecisionTreeQueryList\
)(tree, data)

#endif /* STDDATA_DECISION_TREE_H_ */
