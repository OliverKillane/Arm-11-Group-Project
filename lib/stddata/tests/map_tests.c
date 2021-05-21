#include <map.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/* Helper Functions */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
unsigned long long MapHashFunction(void* item) {
    return 0;
}
#pragma GCC diagnostic pop

bool MapEqFunction(void* a, void* b) {
    return a == b;
}

/* Tests */
void EmptyMapIsEmpty() {
    Map map = NewEmptyMap(MapHashFunction, MapEqFunction);
    assert(MapEmpty(map));
    DeleteMap(map);
}

void MapAddingItems() {
    int nitems = 1e3;
    int keys[nitems];
    int values[nitems];
    Map map = NewEmptyMap(MapHashFunction, MapEqFunction);
    for(int i = 0; i < nitems; i++) {
        assert(MapGet(map, &keys[i]) == NULL);
    }
    for(int i = 0; i < nitems; i++) {
        MapSet(map, &keys[i], &values[nitems - i]);
    }
    for(int i = 0; i < nitems; i++) {
        assert(MapGet(map, &keys[i]) == &values[nitems - i]);
    }
    DeleteMap(map);
}

void MapRemovingItems() {
    int nitems = 1e3;
    int keys[nitems];
    int values[nitems];
    MapEntry kvs[nitems];
    for(int i = 0; i < nitems; i++) {
        kvs[i] = (MapEntry){
            &keys[i],
            &values[nitems - i]
        };
    }
    Map map = NewFilledMap(MapHashFunction, MapEqFunction, nitems, kvs);
    for(int i = 0; i < nitems; i++) {
        assert(MapGet(map, &keys[i]) == &values[nitems - i]);
    }
    for(int i = 0; i < nitems; i++) {
        MapRemove(map, &keys[i]);
    }
    for(int i = 0; i < nitems; i++) {
        assert(MapGet(map, &keys) == NULL);
    }
    DeleteMap(map);
}

void MapTests() {
    EmptyMapIsEmpty();
    MapAddingItems();
    MapRemovingItems();
}