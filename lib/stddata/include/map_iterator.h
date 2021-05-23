/**
 * @file map_iterator.h
 * @author Bartłomiej Cieślar
 * @brief @ref MapIterator and utilities related to it
 */
#ifndef STDDATA_MAP_ITERATOR_H_
#define STDDATA_MAP_ITERATOR_H_

#include <assert.h>
#include "map.h"

/**
 * @brief An iterator for a @ref Map
 * 
 * The MapIterator is mainly used for looping over a map. Example usage in for loops:
 * @code
 * for(MapIterator iter = MapBegin(map); MapIteratorLess(iter, MapEnd(map)); MapIteratorIncr(&iter)) {
 *     printf("%s\n", (char*)(MapIteratorGet(iter).key));
 * }
 * @endcode
 * 
 * @note Most of the interface functions require only the value of an iterator to be passed, except
 *       for the ones modifying it ( @ref MapIteratorIncr and @ref MapIteratorDecr )
 * @note Most of the time it will be used in combination with the MAPFOR macro
 * @warning Changing the internal variables manually outside of the interface functions will result
 *          in an undefined behaviour.
 * @warning Attempting to use an uninitialized MapIterator will result in an undefined behaviour
 */
typedef struct {
    Map map;
    int index;
} MapIterator;

/**
 * @brief A macro for looping over a map
 * 
 * This macro creates a for loop header using iterators to iterate over a map.
 * Example usage:
 * @code
 * MAPFOR(map, iter) {
 *     printf("%s\n", (char*)(MapIteratorGet(iter).key));
 * }
 * @endcode
 * 
 * @param map the map to be iterated over
 * @param iter the name of the iterator that will index the map
 * @warning @p map not being a valid allocated @ref Map results in an undefined behaviour
 */
#define MAPFOR(map, iter) \
    for(MapIterator iter = MapBegin(map); \
        MapIteratorLess(iter, MapEnd(map)); \
        MapIteratorIncr(&iter))

/**
 * @brief Returns an iterator at the beginning of the map
 * 
 * @param map The map to get the beginning iterator to
 * @return An iterator pointing at the first entry of the @p map
 * @warning @p map not being a valid allocated @ref Map results in an undefined behaviour
 */
MapIterator MapBegin(Map map);

/**
 * @brief Returns an iterator at the end of the map
 * 
 * @param map The map to get the end iterator to
 * @return An iterator pointing at the entry behind the last entry of the @p map
 * @warning @p map not being a valid allocated @ref Map results in an undefined behaviour
 */
MapIterator MapEnd(Map map);

/**
 * @brief Checks if the first iterator points before the second
 * 
 * @return @b true if the first iterator points before the second, otherwise @b false
 * @warning the two iterators not pointing at the same map will result in an undefined behaviour
 */
bool MapIteratorLess(MapIterator a, MapIterator b);

/**
 * @brief Compares two iterators
 * 
 * @return -1 if the first iterator points to an entry before the second iterator
 *         0 if the two iterators point to the same entry
 *         1 if the second iterator points to an entry before the first iterator
 * @warning the two iterators not pointing at the same map will result in an undefined behaviour
 */
int MapIteratorCompare(MapIterator a, MapIterator b);

/**
 * @brief Moves the iterator to the next entry in the map
 * 
 * @param iter the pointer to the iterator to be incremented
 * @warning trying to increment an iterator pointing at the end of the map will result in an
 *          undefined behaviour
 */
void MapIteratorIncr(MapIterator *iter);

/**
 * @brief Moves the iterator to the previous entry in the map
 * 
 * @param iter the pointer to the iterator to be incremented
 * @warning trying to increment an iterator pointing at the end of the map will result in an
 *          undefined behaviour
 */
void MapIteratorDecr(MapIterator *iter);

/**
 * @brief Returns the entry the iterator is pointing to
 * 
 * @param iter the iterator to dereference
 * @returns the entry the iterator is pointing at
 */
MapEntry MapIteratorGet(MapIterator iter);


#endif /* STDDATA_MAP_ITERATOR_H_ */