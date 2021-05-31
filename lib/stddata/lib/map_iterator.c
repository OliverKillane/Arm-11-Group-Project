#include <stdlib.h>
#include <map_iterator.h>
#include <map.h>
#include <stdbool.h>

MapIterator MapBegin(Map map) {
    if(MapSize(map) == 0) {
        return (MapIterator) {
            map,
            -1
        };
    }
    int index = map->min_index;

    while(map->data[index].key == NULL || map->data[index].key == MAP_SENTINEL) {
        index++;
    }

    return (MapIterator){
        map,
        index
    };
}

MapIterator MapEnd(Map map) {
    return (MapIterator){
        map,
        -1
    };
}

bool MapIteratorLess(MapIterator a, MapIterator b) {
    assert(a.map == b.map);
    if(a.index == -1) {
        return false;
    }
    if(b.index == -1) {
        return true;
    }
    return a.index < b.index;
}

int MapIteratorCompare(MapIterator a, MapIterator b) {
    return MapIteratorLess(b, a) - MapIteratorLess(a, b);
}

void MapIteratorIncr(MapIterator *iter) {
    assert(iter->index != -1);
    
    do {
        iter->index++;
    } while((iter->map->data[iter->index].key == NULL || iter->map->data[iter->index].key == MAP_SENTINEL) 
            && iter->index <= iter->map->max_index);

    if(iter->index > iter->map->max_index) {
        iter->index = -1;
        return;
    }
}

void MapIteratorDecr(MapIterator *iter) {
    if(iter->index == -1) {
        iter->index = iter->map->max_index + 1;
    }

    do {
        iter->index--;
        assert(iter->index >= iter->map->min_index);
    } while(iter->map->data[iter->index].key == NULL || iter->map->data[iter->index].key == MAP_SENTINEL);
}

MapEntry MapIteratorGet(MapIterator iter) {
    return iter.map->data[iter.index];
}