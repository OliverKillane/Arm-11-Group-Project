/**
 * @file list_iterator.h 
 * @author Bartłomiej Cieślar
 * @brief @ref ListIterator and utilities related to it
 */
#ifndef STDDATA_LIST_ITERATOR_H_
#define STDDATA_LIST_ITERATOR_H_

#include <list.h>
#include <stdbool.h>

/**
 * @brief An iterator for a @ref List
 * 
 * The ListIterator is mainly used for looping over a list, but might also be used to insert new
 * items inside a list. Example usage in for loops:
 * @code
 * for(ListIterator iter = ListBegin(list); !ListIteratorEqual(iter, ListEnd(list)); ListIteratorIncr(&iter)) {
 *     printf("%s\n", (char*)ListIteratorGet(iter));
 * }
 * @endcode
 * 
 * @note Most of the interface functions require only the value of an iterator to be passed, except
 *       for the ones modifying it ( @ref ListIteratorIncr and @ref ListIteratorDecr )
 * @note Most of the time it will be used in combination with the LISTFOR macro
 * @warning Changing the internal variables manually outside of the interface functions will result
 *          in an undefined behaviour.
 * @warning Attempting to use an uninitialized ListIterator will result in an undefined behaviour
 */
typedef struct {
    List list;
    ListNode node;
} ListIterator;

/**
 * @brief A macro for looping over a list
 * 
 * This macro creates a for loop header using iterators to iterate over a list.
 * Example usage:
 * @code
 * LISTFOR(list, iter) {
 *     printf("%s\n", (char*)ListIteratorGet(iter));
 * }
 * @endcode
 * 
 * @param list the list to be iterated over
 * @param iter the name of the iterator that will index the list
 * @warning @p list not being a valid allocated @ref List results in an undefined behaviour
 */
#define LISTFOR(list, iter)\
    for(ListIterator iter = ListBegin(list);\
        !ListIteratorEqual(iter, ListEnd(list));\
        ListIteratorIncr(&iter))

/**
 * @brief Returns an iterator at the beginning of the list
 * 
 * @param list The list to get the beginning iterator to
 * @return An iterator pointing at the first item of the @p list
 * @warning @p list not being a valid allocated @ref List results in an undefined behaviour
 */
ListIterator ListBegin(List list);

/**
 * @brief Returns an iterator at the end of the list
 * 
 * @param list The list to get the end iterator to
 * @return An iterator pointing at the item behind the last item of the @p list
 * @warning @p list not being a valid allocated @ref List results in an undefined behaviour
 */
ListIterator ListEnd(List list);

/**
 * @brief Checks if the two list iterators are equal
 * 
 * @return @b true if the two iterators point at the same place in the list, otherwise @b false
 * @warning the two iterators not pointing at the same list will result in an undefined behaviour
 */
bool ListIteratorEqual(ListIterator a, ListIterator b);

/**
 * @brief Moves the iterator to the next item in the list
 * 
 * @param iter the pointer to the iterator to be incremented
 * @warning trying to increment an iterator pointing at the end of the list will result in an
 *          undefined behaviour
 */
void ListIteratorIncr(ListIterator *iter);

/**
 * @brief Moves the iterator to the previous item in the list
 * 
 * @param iter the pointer to the iterator to be incremented
 * @warning trying to increment an iterator pointing at the end of the list will result in an
 *          undefined behaviour
 */
void ListIteratorDecr(ListIterator *iter);

/**
 * @brief Returns an item the iterator is pointing to
 * 
 * @param iter the iterator to dereference
 * @returns the item the iterator is pointing at
 */
void* ListIteratorGet(ListIterator iter);

/**
 * @brief Sets an item the iterator is pointing to
 * 
 * @param iter the iterator for which to set the item that it is pointing at
 * @param new_item the new value for the item
 * @note the @p new_item may be used to hold an integer value as well if it fits inside a void*
 */
void ListIteratorSet(ListIterator iter, void* new_item);

/**
 * @brief Inserts an item after the item the iterator is pointing to
 * 
 * @param iter the iterator for which to insert the item after
 * @param new_item the value of the item to be inserted
 * @note the @p new_item may be used to hold an integer value as well if it fits inside a void*
 */
void ListIteratorInsertAfter(ListIterator iter, void* new_item);

/**
 * @brief Inserts an item before the item the iterator is pointing to
 * 
 * @param iter the iterator for which to insert the item before
 * @param new_item the value of the item to be inserted
 * @note the @p new_item may be used to hold an integer value as well if it fits inside a void*
 */
void ListIteratorInsertBefore(ListIterator iter, void* new_item);

/**
 * @brief Removes an item the iterator is pointing to 
 * 
 * The function removes the item the iterator is pointing to from the list 
 * and moves the iterator to the next item in the list.
 * 
 * @param iter the iterator for which to remove the item
 * @warning the iterator pointing at the end of the list results in an undefined behaviour
 * @warning if there is another iterator pointing at the same item then trying to access that
 *          iterator in any way later will result in an undefined behaviour
 */
void ListIteratorRemove(ListIterator *iter);

#endif /* STDDATA_LIST_ITERATOR_H_ */