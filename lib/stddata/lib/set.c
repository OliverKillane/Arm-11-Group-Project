/*
 * Implementation based on Google's 2017 HashTable implementation
 */
#include <set.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void* SET_SENTINEL = (void*)1;

static_assert(SET_SIZE_FACTOR > SET_ALLOC_SIZE_FACTOR, "load factor threshold must be less than 1");

/* Helper Functions */
static inline int min(int a, int b) {
    return a < b ? a : b;
}

static inline int max(int a, int b) {
    return a < b ? b : a;
}

int SetProbe(Set set, int index) {
    index++;
    if(index < SetAllocSize(set)) {
        return index;
    }
    return 0;
}

bool SetCheckLoadFactor(Set set) {
    return set->items_num * SET_SIZE_FACTOR >= SetAllocSize(set) * SET_ALLOC_SIZE_FACTOR;
}

int SetFindIndex(Set set, void* item) {
    int index = (set->hash_func(item) & ~((-1) << set->alloc_power));
    while(set->data[index] != NULL
       && (set->data[index] == SET_SENTINEL || !set->eq_func(set->data[index], item))) {
        index = SetProbe(set, index);
    }
    return index;
}

void SetUnsafeInsert(Set set, void* item) {
    int index = SetFindIndex(set, item);
    if(set->data[index] != NULL) {
        return;
    }
    set->data[index] = item;
    set->min_index = min(set->min_index, index);
    set->max_index = max(set->max_index, index);
    set->size++;
    set->items_num++;
}

void SetClearData(int size, void ** data) {
    memset(data, 0, sizeof(void*) * size);
}

void SetGrow(Set set) {
    int old_alloc_size = 1<<set->alloc_power;
    void ** old_data = set->data;
    set->alloc_power++;
    set->data = malloc(sizeof(void*) * (1<<set->alloc_power));
    SetClearData((1<<set->alloc_power), set->data);
    set->size = set->items_num = 0;
    set->min_index = SetAllocSize(set);
    set->max_index = 0;
    for(int i = 0; i < old_alloc_size; i++) {
        if(old_data[i] == SET_SENTINEL || old_data[i] == NULL) {
            continue;
        }
        SetUnsafeInsert(set, old_data[i]);
    }
    free(old_data);
}

/* Methods Definitions */
Set NewEmptySet(unsigned long long (*hash_func)(void*), bool (*eq_func)(void*, void*)) {
    Set out = malloc(sizeof(SetRepr));
    out->data = malloc(sizeof(void*) * (1<<MIN_SET_POWER));
    SetClearData(1<<MIN_SET_POWER, out->data);
    out->alloc_power = MIN_SET_POWER;
    out->items_num = out->size = 0;
    out->hash_func = hash_func;
    out->eq_func = eq_func;
    out->min_index = SetAllocSize(out);
    out->max_index = 0;
    return out;
}

Set NewFilledSet(unsigned long long (*hash_func)(void*), bool (*eq_func)(void*, void*), int size, void* contents[]) {
    Set out = malloc(sizeof(SetRepr));
    out->alloc_power = MIN_SET_POWER;
    out->items_num = size;
    while(SetCheckLoadFactor(out)) {
        out->alloc_power++;
    }
    out->data = malloc(sizeof(void*) * (1<<out->alloc_power));
    SetClearData(1<<out->alloc_power, out->data);
    out->items_num = out->size = 0;
    out->hash_func = hash_func;
    out->eq_func = eq_func;
    out->min_index = SetAllocSize(out);
    out->max_index = 0;
    for(int i = 0; i < size; i++) {
        SetInsert(out, contents[i]);
    }
    return out;
}

int SetSize(Set set) {
    return set->items_num;
}

int SetAllocSize(Set set) {
    return 1<<set->alloc_power;
}

bool SetEmpty(Set set) {
    return SetSize(set) == 0;
}

bool SetQuery(Set set, void* item) {
    return set->data[SetFindIndex(set, item)] != NULL;
}

void SetInsert(Set set, void* item) {
    assert(item != SET_SENTINEL && item != NULL);
    SetUnsafeInsert(set, item);
    if(SetCheckLoadFactor(set)) {
        SetGrow(set);
    }
}

void SetRemove(Set set, void* item) {
    int index = SetFindIndex(set, item);

    if(set->data[index] == NULL && set->data[index] == SET_SENTINEL) {
        return;
    }
    set->data[index] = SET_SENTINEL;
    set->items_num--;
}

void DeleteSet(Set set) {
    free(set->data);
    free(set);
}