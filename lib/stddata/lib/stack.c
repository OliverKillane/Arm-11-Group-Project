#include <vector.h>
#include <stack.h>

Stack NewStack() {
    return NewEmptyVector();
}

void DeleteStack(Stack stack) {
    DeleteVector(stack);
}

void StackPush(Stack stack, void* newItem) {
    VectorPushBack(stack, newItem);
}

void* StackPop(Stack stack) {
    return VectorPopBack(stack);
}

void* StackPeek(Stack stack) {
    return VectorBack(stack);
}

int StackSize(Stack stack) {
    return VectorSize(stack);
}

bool StackEmpty(Stack stack) {
    return VectorEmpty(stack);
}

void StackOptimize(Stack stack) {
    VectorForcedResize(stack, VectorSize(stack));
}