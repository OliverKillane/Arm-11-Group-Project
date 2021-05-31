/**
 * @file list.h
 * @author Bartłomiej Cieślar
 * @brief @ref List and utilities related to it
 */
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

/**
 * @brief The structure representation of a linked list
 * 
 * @note Do not use raw, always use via a @ref List type
 * @warning Changing the internal variables manually outside of the interface functions will result
 *          in an undefined behaviour.
 */
typedef struct {
    ListNode beg;
    ListNode end;
    int size;
} ListRepr;

/**
 * @brief An STL-like Linked List
 * 
 * This is a linked list, meaning that all item insertion operations are in O(1), but accessing 
 * items inside of the list is in O(n).
 * It supports the following operations:
 *     - @ref ListPushFront Adds a new element to the front of the list
 *     - @ref ListPushBack Adds a new element to the back of the the list
 *     - @ref ListPopFront Removes an item from the front of the list and returns it
 *     - @ref ListPopBack Removes an item from the back of the list and returns it
 *     - @ref ListFront Returns the item at the front of the list
 *     - @ref ListBack Returns the item at the back of the list
 *     - @ref ListSet Sets a value of the list at a specific index (in linear time complexity)
 *     - @ref ListGet Returns a value of the list at a specific index (in linear time complexity)
 * 
 * It can be created using @ref NewEmptyList, @ref NewList or @ref NewFilledList, and
 * deallocated using @ref DeleteList.
 * To check its size and test if it is empty, use @ref ListSize and @ref ListEmpty
 * 
 * @note Even though this is only a typedef, do not delcare it as a pointer to @ref ListRepr for
 *       improved code clarity
 * @see @ref ListIterator to loop over a list
 */
typedef ListRepr * List;

/**
 * @brief Creates a new empty @ref List
 * 
 * Dynamically allocates a new empty @ref List using malloc.
 * 
 * @warning In order to avoid memory leaks, please use 
 *          @ref DeleteList to deallocate it once you are done using it.
 */
List NewEmptyList();

/**
 * @brief Creates a new @ref List with @p size items
 * 
 * Dynamically allocates a new empty @ref List using malloc, and fills it with @p size NULL pointer
 * entries.
 * 
 * @param size The number of items to be preallocated
 * @warning In order to avoid memory leaks, please use 
 *          @ref DeleteList to deallocate it once you are done using it.
 */
List NewList(int size);

/**
 * @brief Creates a new @ref List with @p size items
 * 
 * Dynamically allocates a new empty @ref List using malloc, and fills it with the entries in the
 * @p contents array
 * 
 * @param size The size of the @p contents array
 * @param contents The values to fill the list with
 * @warning Passing in an array that is not an array of void* will, unlike with passing single elements,
 *          result in an undefined behaviour.
 * @warning In order to avoid memory leaks, please use 
 *          @ref DeleteList to deallocate it once you are done using it.
 */
List NewFilledList(int size, void* contents[]);

/**
 * @brief Deallocates a @ref List
 *
 * @param list The list to be deallocated
 * @warning Trying to use or deallocate already deallocated @ref List
 *          results in an undefined behaviour
 */
void DeleteList(List list);

/**
 * @brief Returns the number of items inside a list
 * 
 * @param list The list to check the size of
 * @returns The size of the list
 * @warning @p list not being a valid allocated @ref List results in an undefined behaviour
 */
int ListSize(List list);

/**
 * @brief Checks if the list is empty
 * 
 * @param list The list to check the emptiness of
 * @returns @b true if the list has no items, otherwise @b false
 * @warning @p list not being a valid allocated @ref List results in an undefined behaviour
 */
bool ListEmpty(List list);

/**
 * @brief Pushes an item in the back of the list
 * 
 * @param list The list to be modified
 * @param new_item A pointer to an item to push in front of the list
 * 
 * @note the @p new_item may be used to hold an integer value as well if it fits inside a void*
 * @warning @p list not being a valid allocated @ref List results in an undefined behaviour
 */
void ListPushBack(List list, void* new_item);

/**
 * @brief Removes an item from the back of the list
 * 
 * @param list The list to be modified
 * @returns A pointer to the item removed from the list
 * @warning Trying to remove an item from an empty list results in an undefined behaviour
 * @warning @p list not being a valid allocated @ref List results in an undefined behaviour
 */
void* ListPopBack(List list);

/**
 * @brief Pushes an item in the front of the list
 * 
 * @param list The list to be modified
 * @param new_item A pointer to an item to push in front of the list
 * 
 * @note the @p new_item may be used to hold an integer value as well if it fits inside a void*
 * @warning @p list not being a valid allocated @ref List results in an undefined behaviour
 */
void ListPushFront(List list, void* new_item);

/**
 * @brief Removes an item from the front of the list
 * 
 * @param list The list to be modified
 * @returns A pointer to the item removed from the list
 * @warning Trying to remove an item from an empty list results in an undefined behaviour
 * @warning @p list not being a valid allocated @ref List results in an undefined behaviour
 */
void* ListPopFront(List list);

/**
 * @brief Returns an item at the given position in the list (in O(n))
 *
 * @param list The list containing the item to look up
 * @param item_num The index of an item to look up
 * @returns The looked up item
 * @warning @p item_num being outside the list (negative or not smaller than the size of the list)
 *          will result in an undefined behaviour
 * @warning @p list not being a valid allocated @ref List results in an undefined behaviour
 * @see @ref ListIterator to access multiple items in a list
 */
void* ListGet(List list, int item_num);

/**
 * @brief Sets an item at the given position in the list (in O(n))
 * 
 * @param list The list to be modified
 * @param item_num The index in the list to change
 * @param new_item The pointer to an item to be set
 * @note the @p new_item may be used to hold an integer value as well if it fits inside a void*
 * @warning @p item_num being outside the list (negative or not smaller than the size of the list)
 *          will result in an undefined behaviour
 * @warning @p list not being a valid allocated @ref List results in an undefined behaviour
 * @see @ref ListIterator to access multiple items in a list
 */
void ListSet(List list, int item_num, void* new_item);

/**
 * @brief Returns an item from the front of the list without removing it
 * 
 * @param list The list containing the item
 * @returns The item at the front of the list
 * @warning Trying to look up an item in an empty list results in an undefined behaviour
 * @warning @p list not being a valid allocated @ref List results in an undefined behaviour
 */
void* ListFront(List list);

/**
 * @brief Returns an item from the back of the list without removing it
 * 
 * @param list The list containing the item
 * @returns The item at the back of the list
 * @warning Trying to look up an item in an empty list results in an undefined behaviour
 * @warning @p list not being a valid allocated @ref List results in an undefined behaviour
 */
void* ListBack(List list);

#endif /* STDDATA_LIST_H_ */