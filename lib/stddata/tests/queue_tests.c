#include <queue.h>
#include <assert.h>

void EmptyQueueIsEmpty() {
    Queue queue = NewQueue();
    assert(QueueEmpty(queue));
    DeleteQueue(queue);
}

void QueuePushPop() {
    int nitems = 1e4;
    int items[nitems];
    Queue queue = NewQueue();
    for(int i = 0; i < nitems; i++) {
        QueuePush(queue, &items[i]);
    }
    assert(QueueSize(queue) == nitems);
    for(int i = 0; i < nitems; i++) {
        assert(QueuePop(queue) == &items[i]);
    }
    assert(QueueEmpty(queue));
    DeleteQueue(queue);
}

void QueueTests() {
    EmptyQueueIsEmpty();
    QueuePushPop();
}
