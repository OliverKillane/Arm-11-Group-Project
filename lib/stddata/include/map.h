/**
 * @file map.h
 * @author Bartłomiej Cieślar
 * @brief @ref Map and utilities related to it
 */
#ifndef STDDATA_MAP_H_
#define STDDATA_MAP_H_

#include <stdbool.h>

#define MAP_SIZE_FACTOR 10
#define MAP_ALLOC_SIZE_FACTOR 7
#define MIN_MAP_POWER 2

extern void* MAP_SENTINEL;

/**
 * @brief A structure representing an entry in a map
 */
typedef struct {
    /** 
     * @brief the key to the item
    */
    void* key;
    /**
     * @brief The item stored under the key
     */
    void* value;
} MapEntry;

/**
 * @brief The structure representation of a hash map
 * 
 * @note Do not use raw, always use via a @ref Map type
 * @warning Changing the internal variables manually outside of the interface functions will result
 *          in an undefined behaviour.
 */
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

/**
 * @brief An STL-like hash map
 * 
 * This is a hash map, meaning that all operations are in amortized O(1):
 * It supports the following operations:
 *     - @ref MapQuery Checks if a key is in the map
 *     - @ref MapGet Retreives the value of a key in the map
 *     - @ref MapSet Sets a value of a key in the map
 *     - @ref MapRemove Removes a key from a map
 * 
 * It can be created using @ref NewEmptyMap or @ref NewFilledMap, and
 * deallocated using @ref DeleteMap
 * To check its size and test if it is empty, use @ref MapSize and @ref MapEmpty
 * 
 * @note Even though this is only a typedef, do not delcare it as a pointer to @ref MapRepr for
 *       improved code clarity
 * @see @ref MapIterator to loop over a map
 */
typedef MapRepr * Map;

/**
 * @brief Creates a new empty @ref Map
 * 
 * Dynamically allocates a new empty @ref Map using malloc.
 * 
 * @param hash_func The hash function for the map keys
 * @param eq_func The equality function of the map to compare the keys with
 * @warning In order to avoid memory leaks, please use 
 *          @ref DeleteMap to deallocate it once you are done using it.
 */
Map NewEmptyMap(unsigned long long(*hash_func)(void*), bool (*eq_func)(void*, void*));

/**
 * @brief Creates a new @ref Map with @p size entries
 * 
 * Dynamically allocates a new empty @ref Map using malloc, and fills it with the entries in the
 * @p values array
 * 
 * @param hash_func The hash function of the map
 * @param eq_func The equality function of the map to compare the keys with
 * @param size The size of the @p values array
 * @param values The values to fill the map with
 * @warning @p values having keys equal to 0 or 1 will result in an undefined behaviour
 * @warning In order to avoid memory leaks, please use 
 *          @ref DeleteMap to deallocate it once you are done using it.
 */
Map NewFilledMap(unsigned long long(*hash_func)(void*), bool (*eq_func)(void*, void*), int size, MapEntry values[]);

/**
 * @brief Deallocates a @ref Map
 *
 * @param map The map to be deallocated
 * @warning Trying to use or deallocate already deallocated @ref Map
 *          results in an undefined behaviour
 */
void DeleteMap(Map map);

/**
 * @brief Sets a value under a key to a new value
 * 
 * @param map the map to be modified
 * @param key the key to place the @p value under
 * @param value the value to be inserted into the map
 * @note the @p value may be used to hold an integer value as well if it fits inside a void*
 * @warning @p key having a value 0 or 1 will result in an undefined behaviour
 * @warning @p map not being a valid allocated @ref Map results in an undefined behaviour
 */
void MapSet(Map map, void* key, void* value);

/**
 * @brief Retreives a value under a key
 * 
 * @param map the map to retreive the key from
 * @param key the key to retreive value of
 * @returns the value of the key or NULL if the key is not assigned
 * @note if using void* as a store for an integer check if the key is actually in the map
 *       before using this function
 * @see @ref MapQuery for checking if the key is in the map
 * @warning @p key having a value 0 or 1 will result in an undefined behaviour
 * @warning @p map not being a valid allocated @ref Map results in an undefined behaviour
 */
void* MapGet(Map map, void* key);

/**
 * @brief Checks if the key is in the map
 * 
 * @param map The map to check the key for
 * @param key The key to check if is in a map
 * @returns @b true if the key is in the map, otherwise @b false
 * @warning Passing in a pointer to 0 or 1 results in an undefined behaviour
 * @warning @p map not being a valid allocated @ref Map results in an undefined behaviour
 */
bool MapQuery(Map map, void* key);

/**
 * @brief Returns the number of keys inside a map
 * 
 * @param map The map to check the size of
 * @returns The size of the map
 * @note This is not the same as the number of actually allocated entries
 * @see @ref MapAllocSize for the number of allocated entries
 * @warning @p map not being a valid allocated @ref Map results in an undefined behaviour
 */
int MapSize(Map map);

/**
 * @brief Returns the allocated size of a map
 * 
 * @param map The map to check the allocated size of
 * @returns The allocated size of the map
 * @note This is not the same as the number of accessible entries in a map
 * @see @ref MapSize for the number of accessible entries in a map
 * @warning @p map not being a valid allocated @ref Map results in an undefined behaviour
 */
int MapAllocSize(Map map);

/**
 * @brief Checks if the map has no entries
 * 
 * @param map The map to check the emptiness of
 * @returns @b true if the map has no entries, otherwise @b false
 * @warning @p map not being a valid allocated @ref Map results in an undefined behaviour
 */
bool MapEmpty(Map map);

/**
 * @brief Removes the key from the map
 * 
 * @param map The map to remove the key from
 * @param key The key to remove from the map
 * @warning Passing in a pointer equal to 0 or 1 results in an undefined behaviour
 * @warning @p map not being a valid allocated @ref Map results in an undefined behaviour
 */
void MapRemove(Map map, void* key);

#endif /* STDDATA_MAP_H_ */