#ifndef STDDATA_MAP_H_
#define STDDATA_MAP_H_

#include <stdbool.h>

#define MAP_SIZE_FACTOR 10
#define MAP_ALLOC_SIZE_FACTOR 7
#define MIN_MAP_POWER 2

extern void* MAP_SENTINEL;

typedef struct {
    void* key;
    void* value;
} MapEntry;

typedef struct {
    MapEntry *data;
    int alloc_power;
    int size;
    int items_num;
    unsigned long long (*hash_func)(void*);
    bool (*eq_func)(void*, void*);
    int min_index;
    int max_index;
} MapRepr;

typedef MapRepr * Map;

/* 
 * Creates a new empty map
 */
Map NewEmptyMap(unsigned long long(*hash_func)(void*), bool (*eq_func)(void*, void*));

/*
 * Creates a new map filled with specified values
 */
Map NewFilledMap(unsigned long long(*hash_func)(void*), bool (*eq_func)(void*, void*), int size, MapEntry values[]);

/*
 * Deallocates the map
 */
void DeleteMap(Map map);

/*
 * Sets a value under a key to a new value
 */
void MapSet(Map map, void* key, void* value);

/*
 * Retreives a value under a key
 * If there is no key with such value then a NULL pointer will be returned
 */
void* MapGet(Map map, void* key);

/*
 * Checks if a key is in the map
 */
bool MapQuery(Map map, void* key);

/*
 * Returns the number of entries in the map
 */
int MapSize(Map map);

/*
 * Returns the size allocated internally by map
 */
int MapAllocSize(Map map);

/*
 * Checks if the map is empty
 */
bool MapEmpty(Map map);

/*
 * Removes a key from the map
 */
void MapRemove(Map map, void* key);

#endif /* STDDATA_MAP_H_ */