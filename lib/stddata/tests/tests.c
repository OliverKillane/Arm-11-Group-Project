#include "vector_tests.c"
#include "stack_tests.c"
#include "vector_iterator_tests.c"
#include "list_tests.c"
#include "list_iterator_tests.c"
#include "set_tests.c"
#include "deque_tests.c"
#include "queue_tests.c"
#include "set_iterator_tests.c"
#include "map_tests.c"
#include "map_iterator_tests.c"

int main() {
    StackTests();
    VectorTests();
    VectorIteratorTests();
    ListTests();
    ListIteratorTests();
    SetTests();
    DequeTests();
    QueueTests();
    SetIteratorTests();
    MapTests();
    MapIteratorTests();
}