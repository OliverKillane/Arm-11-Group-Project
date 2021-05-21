#include <list.h>
#include <stdbool.h>

typedef struct {
    List list;
    ListNode node;
} ListIterator;

#define LISTFOR(list, iter)\
    for(ListIterator iter = ListBegin(list);\
        !ListIteratorEqual(iter, ListEnd(list));\
        ListIteratorIncr(&iter))

/*
 * Returns an iterator to the beginning of the list
 */
ListIterator ListBegin(List list);

/*
 * Returns an iterator to the end of the list
 */
ListIterator ListEnd(List list);

/*
 * Checks if the two list iterators are equal
 */
bool ListIteratorEqual(ListIterator a, ListIterator b);

/* 
 * Increments the iterator
 * the iterator cannot point to the end of the list
 */
void ListIteratorIncr(ListIterator *iter);

/* 
 * Decrements the iterator
 * the iterator cannot point to the beginning of the list
 */
void ListIteratorDecr(ListIterator *iter);

/*
 * Gets an item the iterator is pointing to
 */
void* ListIteratorGet(ListIterator iter);

/*
 * Sets an item the iterator is pointing to
 */
void ListIteratorSet(ListIterator iter, void* newItem);

/*
 * Inserts a new item after the item the iterator is pointing to
 */
void ListIteratorInsertAfter(ListIterator iter, void* newItem);

/*
 * Inserts a new item before the item the iterator is pointing to
 */
void ListIteratorInsertBefore(ListIterator iter, void* newItem);

/*
 * Removes an item iterator is pointing to and moves the iterator to the next item in the list
 * The iterator must not be pointing to the end of the list
 */
void ListIteratorRemove(ListIterator *iter);