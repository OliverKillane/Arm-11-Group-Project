/*
 * Implementation based on Google's 2017 HashTable implementation
 */
#include <map.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void* MAP_SENTINEL = (void*)1;

static_assert(MAP_SIZE_FACTOR > MAP_ALLOC_SIZE_FACTOR, "load factor threshold must be less than 1");

/* Helper Functions */
static inline int min(int a, int b) {
    return a < b ? a : b;
}

static inline int max(int a, int b) {
    return a < b ? b : a;
}

int MapProbe(Map map, int index) {
    index++;
    if(index < MapAllocSize(map)) {
        return index;
    }
    return 0;
}

bool MapCheckLoadFactor(Map map) {
    return map->items_num * MAP_SIZE_FACTOR >= MapAllocSize(map) * MAP_ALLOC_SIZE_FACTOR;
}

int MapFindIndex(Map map, void* key) {
    int index = (map->hash_func(key) & ~((-1) << map->alloc_power));
    while(map->data[index].key != NULL
       && (map->data[index].key == MAP_SENTINEL || !map->eq_func(map->data[index].key, key))) {
        index = MapProbe(map, index);
    }
    return index;
}

void MapUnsafeSet(Map map, void* key, void* value) {
    int index = MapFindIndex(map, key);
    map->data[index].key = key;
    if(map->data[index].value == NULL) {
        map->size++;
        map->items_num++;
    }
    map->data[index].value = value;
    map->min_index = min(map->min_index, index);
    map->max_index = max(map->max_index, index);
}

void MapClearData(int size, MapEntry *data) {
    memset(data, 0, sizeof(MapEntry) * size);
}

void MapGrow(Map map) {
    int old_alloc_size = 1<<map->alloc_power;
    MapEntry *old_data = map->data;
    map->alloc_power++;
    map->data = malloc(sizeof(MapEntry) * (1<<map->alloc_power));
    MapClearData((1<<map->alloc_power), map->data);
    map->size = map->items_num = 0;
    map->min_index = MapAllocSize(map);
    map->max_index = 0;
    for(int i = 0; i < old_alloc_size; i++) {
        if(old_data[i].key == MAP_SENTINEL || old_data[i].key == NULL) {
            continue;
        }
        MapUnsafeSet(map, old_data[i].key, old_data[i].value);
    }
    free(old_data);
}

/* Methods Definitions */
Map NewEmptyMap(unsigned long long (*hash_func)(void*), bool (*eq_func)(void*, void*)) {
    Map out = malloc(sizeof(MapRepr));
    out->data = malloc(sizeof(MapEntry) * (1<<MIN_MAP_POWER));
    MapClearData(1<<MIN_MAP_POWER, out->data);
    out->alloc_power = MIN_MAP_POWER;
    out->items_num = out->size = 0;
    out->hash_func = hash_func;
    out->eq_func = eq_func;
    out->min_index = MapAllocSize(out);
    out->max_index = 0;
    return out;
}

Map NewFilledMap(unsigned long long (*hash_func)(void*), bool (*eq_func)(void*, void*), int size, MapEntry contents[]) {
    Map out = malloc(sizeof(MapRepr));
    out->alloc_power = MIN_MAP_POWER;
    out->items_num = size;
    while(MapCheckLoadFactor(out)) {
        out->alloc_power++;
    }
    out->data = malloc(sizeof(MapEntry) * (1<<out->alloc_power));
    MapClearData(1<<out->alloc_power, out->data);
    out->items_num = out->size = 0;
    out->hash_func = hash_func;
    out->eq_func = eq_func;
    out->min_index = MapAllocSize(out);
    out->max_index = 0;
    for(int i = 0; i < size; i++) {
        MapSet(out, contents[i].key, contents[i].value);
    }
    return out;
}

int MapSize(Map map) {
    return map->items_num;
}

int MapAllocSize(Map map) {
    return 1<<map->alloc_power;
}

bool MapEmpty(Map map) {
    return MapSize(map) == 0;
}

void* MapGet(Map map, void* key) {
    int index = MapFindIndex(map, key);
    if(map->data[index].key == NULL || map->data[index].key == MAP_SENTINEL) {
        return NULL;
    }
    return map->data[index].value;
}

bool MapQuery(Map map, void* key) {
    int index = MapFindIndex(map, key);
    return map->data[index].key != NULL && map->data[index].key != MAP_SENTINEL;
}

void MapSet(Map map, void* key, void* value) {
    assert(key != MAP_SENTINEL && key != NULL);
    MapUnsafeSet(map, key, value);
    if(MapCheckLoadFactor(map)) {
        MapGrow(map);
    }
}

void MapRemove(Map map, void* key) {
    int index = MapFindIndex(map, key);

    if(map->data[index].key == NULL || map->data[index].key == MAP_SENTINEL) {
        return;
    }
    map->data[index].key = MAP_SENTINEL;
    map->items_num--;
}

void DeleteMap(Map map) {
    free(map->data);
    free(map);
}