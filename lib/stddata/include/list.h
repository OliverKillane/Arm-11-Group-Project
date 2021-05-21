#ifndef STDDATA_LIST_H_
#define STDDATA_LIST_H_
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListNodeReprStruct {
    struct ListNodeReprStruct * next;
    struct ListNodeReprStruct * prev;
    void *value;
} ListNodeRepr;

typedef ListNodeRepr * ListNode;

typedef struct {
    ListNode beg;
    ListNode end;
    int size;
} ListRepr;

typedef ListRepr * List;

/*
 * Creates a new empty list
 */
List NewEmptyList();

/*
 * Creates a new list with a given size
 */
List NewList(int size);

/*
 * Creates a list with the specified contents
 */
List NewFilledList(int size, void* contents[]);

/* 
 * Deallocates a list
 */
void DeleteList(List list);

/* 
 * Returns the size of a list
 */
int ListSize(List list);

/*
 * Checks if a list is empty
 */
bool ListEmpty(List list);

/*
 * Puts new item behind the list
 */
void ListPushBack(List list, void* newItem);

/*
 * Pops an item from behind the list
 * The list must be non-empty
 */
void* ListPopBack(List list);

/*
 * Puts new item in the front of the list
 */
void ListPushFront(List list, void* newItem);

/*
 * Pops an item from the front of the list
 * The list must be non-empty
 */
void* ListPopFront(List list);

/*
 * Gets an item at the given position in the list
 */
void* ListGet(List list, int itemNum);

/*
 * Sets an item at the given position in the list
 */
void ListSet(List list, int itemNum, void* newItem);

/*
 * Gets an item in front of the list
 * The list must have at least one item
 */
void* ListFront(List list);

/*
 * Gets an item in the back of the list
 * The list must have at least one item
 */
void* ListBack(List list);

#endif /* STDDATA_LIST_H_ */