#include <list.h>
#include <stdlib.h>
#include <assert.h>
#include "list_node_utils.h"

List NewEmptyList() {
    List out = malloc(sizeof(ListRepr));
    out->size = 0;
    out->beg = out->end = NewListNode();
    return out;
}

List NewList(int size) {
    List out = NewEmptyList();
    for(int i = 0; i < size; i++) {
        ListPushBack(out, NULL);
    }
    return out;
}

List NewFilledList(int size, void* contents[]) {
    List out = NewEmptyList();
    for(int i = 0; i < size; i++) {
        ListPushBack(out, contents[i]);
    }
    return out;
}

void DeleteList(List list) {
    ListNode curr = list->beg;
    while(curr != list->end) {
        ListNode prev = curr;
        curr = ListNodeNext(curr);
        free(prev);
    }
    free(curr);
    free(list);
}

int ListSize(List restrict list) {
    return list->size;
}

bool ListEmpty(List restrict list) {
    return list->size == 0;
}

void ListPushBack(List restrict list, void* new_item) {
    ListNode old = list->end;
    ListNodeSet(old, new_item);
    
    ListNode newNode = NewListNode();
    ListNodeRewireNext(old, newNode);
    ListNodeRewirePrevious(newNode, old);
    list->end = newNode;
    list->size++;
}

void* ListPopBack(List restrict list) {
    assert(list->size);
    ListNode old = list->end;
    list->end = ListNodePrev(list->end);
    list->size--;
    free(old);

    void* oldItem = ListNodeGet(list->end);
    ListNodeRewireNext(list->end, NULL);
    ListNodeSet(list->end, NULL);
    return oldItem;
}

void ListPushFront(List restrict list, void* new_item) {
    ListNode newNode = NewListNode();
    ListNodeSet(newNode, new_item);

    ListNodeRewireNext(newNode, list->beg);
    ListNodeRewirePrevious(list->beg, newNode);
    list->beg = newNode;
    list->size++;
}

void* ListPopFront(List restrict list) {
    assert(list->size);
    ListNode old = list->beg;
    list->beg = ListNodeNext(list->beg);
    ListNodeRewirePrevious(list->beg, NULL);
    list->size--;

    void* oldItem = ListNodeGet(old);
    free(old);
    return oldItem;
}

void* ListGet(List restrict list, int item_num) {
    assert(item_num >= 0 && item_num < list->size);

    ListNode curr = list->beg;
    for(int i = 0; i < item_num; i++) {
        curr = ListNodeNext(curr);
    }
    return ListNodeGet(curr);
}

void ListSet(List restrict list, int item_num, void* new_item) {
    assert(item_num >= 0 && item_num < list->size);

    ListNode curr = list->beg;
    for(int i = 0; i < item_num; i++) {
        curr = ListNodeNext(curr);
    }
    ListNodeSet(curr, new_item);
}

void* ListFront(List restrict list) {
    assert(list->beg != list->end);
    return ListNodeGet(list->beg);
}

void* ListBack(List restrict list) {
    assert(list->beg != list->end);
    return ListNodeGet(ListNodePrev(list->end));
}