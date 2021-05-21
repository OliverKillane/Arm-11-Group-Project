#ifndef STDDATA_SET_H_
#define STDDATA_SET_H_

#include <stdbool.h>

#define SET_SIZE_FACTOR 10
#define SET_ALLOC_SIZE_FACTOR 7
#define MIN_SET_POWER 2

extern void* SET_SENTINEL;

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

typedef SetRepr * Set;

/*
 * Creates a new empty set
 */
Set NewEmptySet(unsigned long long (*hash_func)(void*), bool (*eq_func)(void*, void*));

/*
 * Creates a new set filled with the given values;
 */
Set NewFilledSet(unsigned long long (*hash_func)(void*), bool (*eq_func)(void*, void*), int size, void* contents[]);

/*
 * Deallocates a set
 */
void DeleteSet(Set set);

/*
 * Returns the size of a set
 */
int SetSize(Set set);

/*
 * Returns the allocated size of a set
 */
int SetAllocSize(Set set);

/*
 * Checks if the set is empty
 */
bool SetEmpty(Set set);

/*
 * Checks if the item is in the set
 */
bool SetQuery(Set set, void* item);

/*
 * Inserts a new item into a set
 * IMPORTANT Do not store any items with value of NULL or 1 (basically not legitimate pointers)
 */
void SetInsert(Set set, void* item);

/*
 * Removes an item from a set
 */
void SetRemove(Set set, void* item);

#endif /* STDDATA_SET_H_ */