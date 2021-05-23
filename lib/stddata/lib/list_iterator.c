#include <list.h>
#include <list_iterator.h>
#include <assert.h>
#include "list_node_utils.h"

ListIterator ListBegin(List list) {
    return (ListIterator){
        list,
        list->beg
    };
}

ListIterator ListEnd(List list) {
    return (ListIterator){
        list,
        list->end
    };
}

bool ListIteratorEqual(ListIterator a, ListIterator b) {
    assert(a.list == b.list);
    return a.node == b.node;
}

void ListIteratorIncr(ListIterator *iter) {
    assert(iter->node != iter->list->end);
    iter->node = ListNodeNext(iter->node);
}

void ListIteratorDecr(ListIterator *iter) {
    assert(iter->node != iter->list->beg);
    iter->node = ListNodePrev(iter->node);
}

void* ListIteratorGet(ListIterator iter) {
    return ListNodeGet(iter.node);
}

void ListIteratorSet(ListIterator iter, void* new_item) {
    ListNodeSet(iter.node, new_item);
}

void ListIteratorInsertAfter(ListIterator iter, void* new_item) {
    if(iter.node != iter.list->end) {
        ListNode next = ListNodeNext(iter.node);
        ListNode newNode = NewListNode();
        ListNodeSet(newNode, new_item);
        ListNodeRewireNext(iter.node, newNode);
        ListNodeRewirePrevious(newNode, iter.node);
        ListNodeRewireNext(newNode, next);
        ListNodeRewirePrevious(next, newNode);
        iter.list->size++;
    } else {
        ListPushBack(iter.list, new_item);
    }
}

void ListIteratorInsertBefore(ListIterator iter, void* new_item) {
    if(iter.node != iter.list->beg) {
        ListNode prev = ListNodePrev(iter.node);
        ListNode newNode = NewListNode();
        ListNodeSet(newNode, new_item);
        ListNodeRewirePrevious(iter.node, newNode);
        ListNodeRewireNext(newNode, iter.node);
        ListNodeRewirePrevious(newNode, prev);
        ListNodeRewireNext(prev, newNode);
        iter.list->size++;
    } else {
        ListPushFront(iter.list, new_item);
    }
}

void ListIteratorRemove(ListIterator *iter) {
    assert(iter->node != iter->list->end);
    if(iter->node == iter->list->beg) {
        ListPopFront(iter->list);
        *iter = ListBegin(iter->list);
    } else {
        ListNode prev = ListNodePrev(iter->node);
        ListNode old = iter->node;
        iter->node = ListNodeNext(iter->node);
        free(old);
        ListNodeRewireNext(prev, iter->node);
        ListNodeRewirePrevious(iter->node, prev);
        iter->list->size--;
    }
    
}