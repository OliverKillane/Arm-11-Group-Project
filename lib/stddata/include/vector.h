#ifndef STDDATA_VECTOR_H_
#define STDDATA_VECTOR_H_
#include <stdbool.h>

#define MIN_VECTOR_SIZE 64

typedef struct {
    void **data;
    int size;
    int alloc_size;
} VectorRepr;

typedef VectorRepr * Vector;

/* 
 * Creates a new vector of a given size
 */
Vector NewVector(int size);

/* 
 * Creates a new empty vector
 */
Vector NewEmptyVector();

/*
 * Creates a vector and fills it with contents
 */
Vector NewFilledVector(int size, void* contents[]);

/*
 * Deallocates a vector
 */
void DeleteVector(Vector vector);


/*
 * Retreives an element item a vector
 * The itemNum must be within [0, size)
 */
void* VectorGet(Vector vector, int itemNum);

/*
 * Sets a field in a vector
 * The itemNum must be within [0, size)
 */
void VectorSet(Vector vector, int itemNum, void* newItem);

/*
 * Returns the size of a vector
 */
int VectorSize(Vector vector);

/*
 * Checks if a vector is empty
 */
bool VectorEmpty(Vector vector);

/*
 * Returns the allocated size of a vector
 */
int VectorAllocSize(Vector vector);

/*
 * Resizes the vector to a given size
 */
void VectorResize(Vector vector, int size);

/*
 * Resizes the vector to 0
 */
void VectorClear(Vector vector);

/*
 * Forces an allocated size of a vector to be as close to the actual size as possible
 * (no smaller than MIN_VECTOR_SIZE)
 */
void VectorForcedResize(Vector vector, int size);

/*
 * Sets the allocated size of a vector to be MIN_VECTOR_SIZE
 * and the size to 0
 */

void VectorForcedClear(Vector vector);

/*
 * Pushes a new item at the end of a vector
 */
void VectorPushBack(Vector vector, void* newItem);

/*
 * Pops an item from the back of the vector
 * The vector's size must be positive
 */
void* VectorPopBack(Vector vector);

/*
 * Returns an item at the back of the vector
 * The vector's size must be positive
 */
void* VectorBack(Vector vector);

#endif /* STDDATA_VECTOR_H_ */