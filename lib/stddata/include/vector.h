/**
 * @file vector.h
 * @author Bartłomiej Cieślar
 * @brief @ref Vector and utilities related to it
 */
#ifndef STDDATA_VECTOR_H_
#define STDDATA_VECTOR_H_
#include <stdbool.h>

/**
 * @brief The absolute minimum size that the vector can allocate
 * @note Can be changed in this header file if a different value is needed
 * @warning The value must be positive
 */
#define MIN_VECTOR_SIZE 64

/**
 * @brief The structure representation of a vector
 * 
 * @note Do not use raw, always use via a @ref Vector type
 * @warning Changing the internal variables manually outside of the interface functions will result
 *          in an undefined behaviour.
 */
typedef struct {
    void **data;
    unsigned int size;
    unsigned int alloc_size;
} VectorRepr;

/**
 * @brief An STL-like Vector
 * 
 * This is a vector implemented using allocated size doubling, meaning that all of the basic
 * operations on it are in O(1) (except for @ref VectorForcedResize, @ref VectorForcedClear and @ref VectorResize which are all pessimistically linear).
 * It supports the following operations:
 *     - @ref VectorSet Sets a value of the vector at a specific index (in linear time complexity)
 *     - @ref VectorGet Returns a value of the vector at a specific index (in linear time complexity)
 *     - @ref VectorResize Resizes a vector
 *     - @ref VectorClear Resizes a vector to 0
 *     - @ref VectorForcedResize Resizes a vector and reallocates it so that the allocated size is as close to the actual size as possible (no smaller than @ref MIN_VECTOR_SIZE )
 *     - @ref VectorForcedClear Clears a vector and reallocates it to an allocated size of @ref MIN_VECTOR_SIZE
 *     - @ref VectorPushBack Adds an element at the end of the vector
 *     - @ref VectorPopBack Removes an element from the end of the vector
 * 
 * It can be created using @ref NewEmptyVector, @ref NewVector or @ref NewFilledVector, and
 * deallocated using @ref DeleteVector.
 * To check its size and test if it is empty, use @ref VectorSize and @ref VectorEmpty
 * 
 * @note Even though this is only a typedef, do not delcare it as a pointer to @ref VectorRepr for
 *       improved code clarity
 * @see @ref VectorIterator to loop over a vector
 */
typedef VectorRepr * Vector;

/**
 * @brief Creates a new @ref Vector with @p size items
 * 
 * Dynamically allocates a new empty @ref Vector using malloc
 * entries.
 * 
 * @param size The number of items to be preallocated
 * @note unlike with @ref List, the new vector is not defined to be filled with any particular values
 * @warning In order to avoid memory leaks, please use 
 *          @ref DeleteVector to deallocate it once you are done using it.
 */
Vector NewVector(unsigned int size);

/**
 * @brief Creates a new empty @ref Vector
 * 
 * Dynamically allocates a new empty @ref Vector using malloc.
 * 
 * @warning In order to avoid memory leaks, please use 
 *          @ref DeleteVector to deallocate it once you are done using it.
 */
Vector NewEmptyVector();

/**
 * 
 * @brief Creates a new @ref Vector with @p size items
 * 
 * Dynamically allocates a new empty @ref Vector using malloc, and fills it with the entries in the
 * @p contents array
 * 
 * @param size The size of the @p contents array
 * @param contents The values to fill the vector with
 * @warning Passing in an array that is not an array of void* will, unlike with passing single elements,
 *          result in an undefined behaviour.
 * @warning In order to avoid memory leaks, please use 
 *          @ref DeleteVector to deallocate it once you are done using it.
 */
Vector NewFilledVector(unsigned int size, void* contents[]);

/**
 * @brief Deallocates a @ref Vector
 *
 * @param vector The vector to be deallocated
 * @warning Trying to use or deallocate already deallocated @ref Vector
 *          results in an undefined behaviour
 */
void DeleteVector(Vector vector);

/**
 * @brief Returns an item at the given position in the vector
 *
 * @param vector The vector containing the item to look up
 * @param item_num The index of an item to look up
 * @returns The looked up item
 * @warning @p item_num being outside the vector (negative or not smaller than the size of the vector)
 *          will result in an undefined behaviour
 * @warning @p vector not being a valid allocated @ref Vector results in an undefined behaviour
 * @see @ref VectorIterator to loop over the elements in the vector
 */
void* VectorGet(Vector vector, int item_num);

/**
 * @brief Sets an item at the given position in the vector
 * 
 * @param vector The vector to be modifier
 * @param item_num The index in the vector to change
 * @param new_item The pointer to an item to be set
 * @note the @p new_item may be used to hold an integer value as well if it fits inside a void*
 * @warning @p item_num being outside the vector (negative or not smaller than the size of the vector)
 *          will result in an undefined behaviour
 * @warning @p vector not being a valid allocated @ref Vector results in an undefined behaviour
 * @see @ref VectorIterator to loop over the elements in the vector
 */
void VectorSet(Vector vector, int item_num, void* new_item);

/**
 * @brief Returns the number of items inside a vector
 * 
 * @param vector The vector to check the size of
 * @returns The size of the vector
 * @note This is not the same as the number of actually allocated entries
 * @see @ref VectorAllocSize for the number of allocated entries
 * @warning @p vector not being a valid allocated @ref Vector results in an undefined behaviour
 */
int VectorSize(Vector vector);

/**
 * @brief Checks if the vector is empty
 * 
 * @param vector The vector to check the emptiness of
 * @returns @b true if the vector has no items, otherwise @b false
 * @warning @p vector not being a valid allocated @ref Vector results in an undefined behaviour
 */
bool VectorEmpty(Vector vector);

/**
 * @brief Returns the allocated size of a vector
 * 
 * @param vector The vector to check the allocated size of
 * @returns The allocated size of the vector
 * @note This is not the same as the number of accessible entries in a vector
 * @see @ref VectorSize for the number of accessible entries in a vector
 * @warning @p vector not being a valid allocated @ref Vector results in an undefined behaviour
 */
int VectorAllocSize(Vector vector);

/**
 * @brief Resizes the vector to a given size
 *
 * @param vector The vector to be modified
 * @param size The size to resize the vector to
 * @note This operation is pesimistically of linear time complexity - unless the vector is resized to a smaller size
 * @note This does not guarantee that the allocated size will be exactly the same as the size of a vector
 * @see @ref VectorForcedResize to be sure that the allocated size is as close to the actual size as possible
 * @warning @p vector not being a valid allocated @ref Vector results in an undefined behaviour
 */
void VectorResize(Vector vector, unsigned int size);

/**
 * @brief Resizes the vector to size 0
 * 
 * @param vector The vector to be modified
 * @note This does not guarantee that the allocated size will be exactly 0
 * @see @ref VectorForcedResize to be sure that the allocated size is as small as possible
 * @warning @p vector not being a valid allocated @ref Vector results in an undefined behaviour
 */
void VectorClear(Vector vector);

/**
 * @brief Forces an allocated size of a vector to be as close to the actual size as possible
 * 
 * The vector gets resized to the @p size and reallocated to be as close to that size as possible.
 * The final allocated size will be min( @p size , @ref MIN_VECTOR_SIZE ).
 * 
 * @param vector The vector to be modified
 * @param size The size to resize the vector to
 * @note This operation is of linear
 * @warning @p vector not being a valid allocated @ref Vector results in an undefined behaviour
 */
void VectorForcedResize(Vector vector, unsigned int size);

/**
 * @brief Forces an allocated size of a vector to be @ref MIN_VECTOR_SIZE and the size to be 0
 * 
 * @param vector The vector to be modified
 * @note This operation is of linear complexity
 * @warning @p vector not being a valid allocated @ref Vector results in an undefined behaviour
 */
void VectorForcedClear(Vector vector);

/**
 * @brief Pushes an item in the back of the vector
 * 
 * @param vector The vector to be modified
 * @param new_item A pointer to an item to push in front of the vector
 * 
 * @note the @p new_item may be used to hold an integer value as well if it fits inside a void*
 * @warning @p vector not being a valid allocated @ref Vector results in an undefined behaviour
 */
void VectorPushBack(Vector vector, void* new_item);

/**
 * @brief Removes an item from the back of the vector
 * 
 * @param vector The vector to be modified
 * @returns A pointer to the item removed from the vector
 * @warning Trying to remove an item from an empty vector results in an undefined behaviour
 * @warning @p vector not being a valid allocated @ref Vector results in an undefined behaviour
 */
void* VectorPopBack(Vector vector);

/**
 * @brief Returns an item from the back of the vector without removing it
 * 
 * @param vector The vector containing the item
 * @returns The item at the back of the vector
 * @warning Trying to look up an item in an empty vector results in an undefined behaviour
 * @warning @p vector not being a valid allocated @ref Vector results in an undefined behaviour
 */
void* VectorBack(Vector vector);

#endif /* STDDATA_VECTOR_H_ */