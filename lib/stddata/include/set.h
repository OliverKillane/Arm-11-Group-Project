/**
 * @file set.h 
 * @author Bartłomiej Cieślar
 * @brief @ref Set and utilities related to it
 */
#ifndef STDDATA_SET_H_
#define STDDATA_SET_H_

#include <stdbool.h>

#define SET_SIZE_FACTOR 10
#define SET_ALLOC_SIZE_FACTOR 7
#define MIN_SET_POWER 2

extern void* SET_SENTINEL;

/**
 * @brief The structure representation of a hash set
 * 
 * @note Do not use raw, always use via a @ref Set type
 * @warning Changing the internal variables manually outside of the interface functions will result
 *          in an undefined behaviour.
 */
typedef struct {
    void **data;
    int alloc_power;
    int size;
    int items_num;
    unsigned long long (*hash_func)(void*);
    bool (*eq_func)(void*, void*);
    int min_index;
    int max_index;
} SetRepr;

/**
 * @brief An STL-like hash set
 * 
 * This is a hash set, meaning that all operations are in amortized O(1):
 * It supports the following operations:
 *     - @ref SetQuery Checks if an item is in the set
 *     - @ref SetInsert Adds an item to a set
 *     - @ref SetRemove Removes an item from a set
 * 
 * It can be created using @ref NewEmptySet or @ref NewFilledSet, and
 * deallocated using @ref DeleteSet
 * To check its size and test if it is empty, use @ref SetSize and @ref SetEmpty
 * 
 * @note Even though this is only a typedef, do not delcare it as a pointer to @ref SetRepr for
 *       improved code clarity
 * @see @ref SetIterator to loop over a set
 */
typedef SetRepr * Set;

/**
 * @brief Creates a new empty @ref Set
 * 
 * Dynamically allocates a new empty @ref Set using malloc.
 * 
 * @param hash_func The hash function of the set
 * @param eq_func The equality function of the set to compare the items with
 * 
 * @warning In order to avoid memory leaks, please use 
 *          @ref DeleteSet to deallocate it once you are done using it.
 */
Set NewEmptySet(unsigned long long (*hash_func)(void*), bool (*eq_func)(void*, void*));

/**
 * @brief Creates a new @ref Set with @p size items
 * 
 * Dynamically allocates a new empty @ref Set using malloc, and fills it with the entries in the
 * @p contents array
 * 
 * @param hash_func The hash function of the set
 * @param eq_func The equality function of the set to compare the items with
 * @param size The size of the @p contents array
 * @param contents The values to fill the set with
 * @warning Passing in an array that is not an array of void* will, unlike with passing single elements,
 *          result in an undefined behaviour.
 * @warning @p contents having items equal to 0 or 1 will result in an undefined behaviour
 * @warning In order to avoid memory leaks, please use 
 *          @ref DeleteSet to deallocate it once you are done using it.
 */
Set NewFilledSet(unsigned long long (*hash_func)(void*), bool (*eq_func)(void*, void*), int size, void* contents[]);

/**
 * @brief Deallocates a @ref Set
 *
 * @param set The set to be deallocated
 * @warning Trying to use or deallocate already deallocated @ref Set
 *          results in an undefined behaviour
 */
void DeleteSet(Set set);

/**
 * @brief Returns the number of items inside a set
 * 
 * @param set The set to check the size of
 * @returns The size of the set
 * @note This is not the same as the number of actually allocated entries
 * @see @ref SetAllocSize for the number of allocated entries
 * @warning @p set not being a valid allocated @ref Set results in an undefined behaviour
 */
int SetSize(Set set);

/**
 * @brief Returns the allocated size of a set
 * 
 * @param set The set to check the allocated size of
 * @returns The allocated size of the set
 * @note This is not the same as the number of accessible entries in a set
 * @see @ref SetSize for the number of accessible entries in a set
 * @warning @p set not being a valid allocated @ref Set results in an undefined behaviour
 */
int SetAllocSize(Set set);

/**
 * @brief Checks if the set is empty
 * 
 * @param set The set to check the emptiness of
 * @returns @b true if the set has no items, otherwise @b false
 * @warning @p set not being a valid allocated @ref Set results in an undefined behaviour
 */
bool SetEmpty(Set set);

/**
 * @brief Checks if the item is in the set
 * 
 * @param set The set to check the item for
 * @param item The item to check if is in a set
 * @returns @b true if the item is in the set, otherwise @b false
 * @warning Passing in a pointer to 0 or 1 results in an undefined behaviour
 * @warning @p set not being a valid allocated @ref Set results in an undefined behaviour
 */
bool SetQuery(Set set, void* item);

/**
 * @brief Inserts the item into the set
 * 
 * @param set The set to insert the item into
 * @param item The item to insert into the set
 * @warning Passing in a pointer equal to 0 or 1 results in an undefined behaviour
 * @warning @p set not being a valid allocated @ref Set results in an undefined behaviour
 */
void SetInsert(Set set, void* item);

/**
 * @brief Removes the item from the set
 * 
 * @param set The set to remove the item from
 * @param item The item to remove from the set
 * @warning Passing in a pointer equal to 0 or 1 results in an undefined behaviour
 * @warning @p set not being a valid allocated @ref Set results in an undefined behaviour
 */
void SetRemove(Set set, void* item);

#endif /* STDDATA_SET_H_ */