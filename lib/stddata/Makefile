CC=gcc
CSANITIZERS= -fsanitize=address,return,unreachable,null,bounds
CFLAGS= -g -fPIC -O3 -Wall -pedantic -std=c17 -Iinclude -Wno-int-conversion

default: clean test library

build/tests/tests: build/tests/tests.o build/tests/vector.o build/tests/stack.o\
				   build/tests/vector_iterator.o build/tests/list_node_utils.o build/tests/list.o\
				   build/tests/list_iterator.o  build/tests/set.o build/tests/queue.o\
				   build/tests/deque.o build/tests/set_iterator.o build/tests/map.o\
				   build/tests/map_iterator.o build/tests/decision_tree.o
	$(CC) $^ $(CSANITIZERS) -o build/tests/tests

build/tests/%.o: 
	$(CC) -c $(CFLAGS) $(CSANITIZERS) $^ -o $@

build/%.o:
	$(CC) -c $(CFLAGS) $^ -o $@

build/tests/tests.o: tests/tests.c
build/tests/vector.o: lib/vector.c
build/tests/stack.o: lib/stack.c
build/tests/vector_iterator.o: lib/vector_iterator.c
build/tests/list_node_utils.o: lib/list_node_utils.c
build/tests/list.o: lib/list.c
build/tests/list_iterator.o: lib/list_iterator.c
build/tests/set.o: lib/set.c
build/tests/queue.o: lib/queue.c
build/tests/deque.o: lib/deque.c
build/tests/set_iterator.o: lib/set_iterator.c
build/tests/map.o: lib/map.c
build/tests/map_iterator.o: lib/map_iterator.c
build/tests/decision_tree.o: lib/decision_tree.c

build/vector.o: lib/vector.c
build/stack.o: lib/stack.c
build/vector_iterator.o: lib/vector_iterator.c
build/list_node_utils.o: lib/list_node_utils.c
build/list.o: lib/list.c
build/list_iterator.o: lib/list_iterator.c
build/set.o: lib/set.c
build/queue.o: lib/queue.c
build/deque.o: lib/deque.c
build/set_iterator.o: lib/set_iterator.c
build/map.o: lib/map.c
build/map_iterator.o: lib/map_iterator.c
build/hash_utils.o: lib/hash_utils.c
build/decision_tree.o: lib/decision_tree.c

clean:
	rm -rf build/*
	rm -rf bin/*
	mkdir build/tests

test: build/tests/tests
	build/tests/tests

library: build/vector.o build/stack.o build/vector_iterator.o build/list_node_utils.o\
		 build/list.o build/list_iterator.o build/set.o build/queue.o build/deque.o\
		 build/set_iterator.o build/map.o build/map_iterator.o build/hash_utils.o\
		 build/decision_tree.o
	
	ar rcs bin/libstddata.a $^

.PHONY: clean default library
