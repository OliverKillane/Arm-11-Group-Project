#include <list.h>
#include <stdlib.h>
#include "list_node_utils.h"

ListNode NewListNode() {
    ListNode out = malloc(sizeof(ListNodeRepr));
    out->prev = out->next = out->value = NULL;
    return out;
}

void* ListNodeGet(ListNode restrict node) {
    return node->value;
}

void ListNodeSet(ListNode restrict node, void *newItem) {
    node->value = newItem;
}

ListNode ListNodeNext(ListNode restrict node) {
    return node->next;
}

ListNode ListNodePrev(ListNode restrict node) {
    return node->prev;
}

void ListNodeRewireNext(ListNode restrict node, ListNode newNext) {
    node->next = newNext;
}

void ListNodeRewirePrevious(ListNode restrict node, ListNode newNext) {
    node->prev = newNext;
}