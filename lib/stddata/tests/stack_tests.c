#include <stack.h>
#include <vector.h>
#include <assert.h>

void NewStackEmpty() {
    Stack stack = NewStack();
    assert(StackEmpty(stack));
    DeleteStack(stack);
}

void StackPushPop() {
    int nitems = 5;
    int items[] = {324, 5, 12, 5, 7};
    Stack stack = NewStack();
    for(int i = 0; i < nitems; i++) {
        StackPush(stack, &items[i]);
        assert(StackPeek(stack) == &items[i]);
    }
    assert(StackSize(stack) == nitems);
    for(int i = nitems - 1; i >= 0; i--) {
        assert(StackPop(stack) == &items[i]);
    }
    assert(StackEmpty(stack));
    DeleteStack(stack);
}

void StackSizeAndOptimize() {
    int nsizes = 5;
    int sizes[] = {123, 66, 22, 876, 64};
    int dummy = 1;
    for(int i = 0; i < nsizes; i++) {
        Stack stack = NewStack();
        for(int j = 0; j < sizes[i]; j++) {
            StackPush(stack, &dummy);
        }
        assert(StackSize(stack) == sizes[i]);
        if(sizes[i] >= MIN_VECTOR_SIZE) {
            StackOptimize(stack);
            assert(StackSize(stack) == VectorAllocSize(stack));
        }
        DeleteStack(stack);
    }
}

void StackTests() {
    NewStackEmpty();
    StackPushPop();
    StackSizeAndOptimize();
}