#include <map_iterator.h>
#include <map.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
unsigned long long MapIteratorHashFunction(void* item) {
    return (unsigned long long)item;
}
#pragma GCC diagnostic pop

bool MapIteratorEqFunction(void* a, void* b) {
    return a == b;
}

void EmptyMapBeginEnd() {
    Map map = NewEmptyMap(MapIteratorHashFunction, MapIteratorEqFunction);
    assert(MapIteratorCompare(MapBegin(map), MapEnd(map)) == 0);
    DeleteMap(map);
}

void NonEmptyMapBegin() {
    int k = 2, v = 3;
    Map map = NewFilledMap(
        MapIteratorHashFunction, 
        MapIteratorEqFunction, 
        1, 
        (MapEntry[]){(MapEntry){&k, &v}}
    );
    assert(MapIteratorGet(MapBegin(map)).key == &k);
    assert(MapIteratorGet(MapBegin(map)).value == &v);
    DeleteMap(map);
}

int MapSortComp(const void* a, const void* b) {
    return (*(void**)a > *(void**)b) - (*(void**)b > *(void**)a);
}

void MapIterating() {
    int nitems = 1e3;
    int keys[nitems];
    int values[nitems];
    MapEntry entries[nitems];
    for(int i = 0; i < nitems; i++) {
        entries[i] = (MapEntry){&keys[i], &values[nitems - i]};
    }
    Map map = NewFilledMap(MapIteratorHashFunction, MapIteratorEqFunction, nitems, entries);

    int i = 0;
    void* found[nitems];
    for(MapIterator iter = MapBegin(map); 
        MapIteratorLess(iter, MapEnd(map)); 
        MapIteratorIncr(&iter)) {
        found[i++] = MapIteratorGet(iter).key;
    }
    assert(i == nitems);
    qsort(found, nitems, sizeof(void*), MapSortComp);
    for(int i = 0; i < nitems; i++) {
        assert(found[i] == entries[i].key);
    }
    DeleteMap(map);
}

void MapFor() {
    int nitems = 1e3;
    int keys[nitems];
    int values[nitems];
    MapEntry entries[nitems];
    for(int i = 0; i < nitems; i++) {
        entries[i] = (MapEntry){&keys[i], &values[nitems - i]};
    }
    Map map = NewFilledMap(MapIteratorHashFunction, MapIteratorEqFunction, nitems, entries);

    int i = 0;
    void* found[nitems];
    MAPFOR(map, iter) {
        found[i++] = MapIteratorGet(iter).key;
    }
    assert(i == nitems);
    qsort(found, nitems, sizeof(void*), MapSortComp);
    for(int i = 0; i < nitems; i++) {
        assert(found[i] == entries[i].key);
    }
    DeleteMap(map);
}

void MapIteratorTests() {
    EmptyMapBeginEnd();
    NonEmptyMapBegin();
    MapIterating();
    MapFor();
}