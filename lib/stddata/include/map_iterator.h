#ifndef STDDATA_MAP_ITERATOR_H_
#define STDDATA_MAP_ITERATOR_H_

#include <assert.h>
#include "map.h"

typedef struct {
    Map map;
    int index;
} MapIterator;

#define MAPFOR(map, iter) \
    for(MapIterator iter = MapBegin(map); \
        MapIteratorLess(iter, MapEnd(map)); \
        MapIteratorIncr(&iter))

/*
 * Returns an iterator to the beginning of the list
 */
MapIterator MapBegin(Map map);

/*
 * Returns an iterator to the end of the list
 */
MapIterator MapEnd(Map map);

/*
 * Checks if the first iterator points before the second
 */
bool MapIteratorLess(MapIterator a, MapIterator b);

/*
 * Comparator function for map iterators
 */
int MapIteratorCompare(MapIterator a, MapIterator b);

/*
 * Advances the iterator to the next item in the map
 * The iterator cannot be pointing to the end of the list
 */
void MapIteratorIncr(MapIterator *iter);

/* 
 * Retreats the iterator to the previous item in the map
 * The iterator cannot be pointing to the beginning of the list
 */
void MapIteratorDecr(MapIterator *iter);

/*
 * Returns the value of the item the iterator is pointing to
 */
MapEntry MapIteratorGet(MapIterator iter);


#endif /* STDDATA_MAP_ITERATOR_H_ */