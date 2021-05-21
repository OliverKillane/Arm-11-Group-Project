#ifndef STDDATA_LIST_NODE_UTILS_H_
#define STDDATA_LIST_NODE_UTILS_H_

ListNode NewListNode();

void* ListNodeGet(ListNode restrict node);

void ListNodeSet(ListNode restrict node, void *newItem);

ListNode ListNodeNext(ListNode restrict node);

ListNode ListNodePrev(ListNode restrict node);

void ListNodeRewireNext(ListNode restrict node, ListNode newNext);

void ListNodeRewirePrevious(ListNode restrict node, ListNode newNext);

#endif /* STDDATA_LIST_NODE_UTILS_H_ */