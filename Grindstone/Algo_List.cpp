//
//  Algo_List.cpp
//  Grindstone
//
//  Created by sphota on 8/12/16.
//  Copyright © 2016 Intellex. All rights reserved.
//

#include "Algo_List.hpp"

/* delete node with only access to node */

void deleteNode(ListNode* node) {
	if(node->next) {
		node->val=node->next->val;
		node->next=node->next->next;
	}
	else
		delete node;
}

/* Plus One Linked List */
static void plusOneAux(ListNode* head, bool & flag) {
	if (not head) return;
	plusOneAux(head->next, flag);
	if (flag) {
		if (head->val + 1 == 10)
			head->val = 0;
		else {
			head->val++;
			flag = false;
		}
	}
}

ListNode* plusOne(ListNode* head) {
	if (not head) return NULL;
	bool flag = true;
	plusOneAux(head, flag);
	if (head->val == 0) { // overflow
		ListNode *one = new ListNode(1);
		ListNode *temp = head;
		one->next = temp;
		head = one;
	}
	return head;
}

/* removing elements from linked list recursively */

ListNode* removeElements(ListNode* head, int val) {
	if (head == NULL) { return NULL; }
	/* the program will not move past this line until the base case is reached */
	head->next = removeElements(head->next, val);
	if (head->val == val) {
		ListNode *temp = head->next;
		delete head;
		return temp;
	}
	return head;
}

/* removing duplicates from sorted list */

ListNode* deleteDuplicates(ListNode* head) {
	if(head == NULL) return NULL;
	ListNode *temp = head;
	while (temp->next not_eq NULL) {
		ListNode *n = temp->next;
		if (temp->val == temp->next->val) {
			temp->next = n->next;
			delete n;
		} else
			temp = n;
	}
	return head;
}

/* separate odd and even nodes (slow) */

static ListNode* append(ListNode *list, ListNode *node) {
     ListNode *temp = list;
     if (temp == NULL) {
         return node;
     } else  {
         while (temp->next) temp = temp->next;
         temp->next = node;
         return list;
     }
 }

ListNode* oddEvenList(ListNode* head) {
	if (head == NULL) return NULL;
	 ListNode *evenList = NULL;
	 ListNode *oddList = NULL;
	 int counter = 1;
	 while (head) {
	     ListNode *p = new ListNode(head->val);
	     if (counter % 2 != 0) {
	         oddList = append(oddList, p);
	     } else {
	         evenList = append(evenList, p);
	     }
	     counter = counter + 1;
	     head = head->next;
	 }
	 return append(oddList, evenList);
}

/* reverse list in place */

ListNode* reverseList(ListNode* head) {
	if(head == NULL) return head;
	ListNode *p = head;
	while (p->next) {
		ListNode *n = p->next;
		p->next = n->next;
		n->next = head;
		head = n;
	}
	
	return head;
}

ListNode* insert(ListNode* current, ListNode* prev, ListNode* head) {
	if ((prev->val == head->val && prev->val <= current->val) || prev == nullptr) return prev;
	
	prev->next = insert(current, prev, head);
	
	return prev;
}

ListNode* insertionSortList(ListNode* head) {
	if (head == nullptr) return head;
	ListNode *first = head->next;
	if (first == nullptr) return head;
	ListNode *p = head->next;
	ListNode *prev = head;
	ListNode *key;
	while (p != nullptr) {
		key = p;
		insert(key, prev, head);
		prev->next = key;
		p = p->next;
		prev = prev->next;
	}
	
	return head;
}

/* swap nodes in pairs */
ListNode* findPrev(ListNode *p, ListNode *root) {
	if (p == root) return root;
	while (root) {
		if (root->next == p) {
			return root;
		}
		root = root->next;
	}
	return NULL;
}

ListNode* swapPairs(ListNode* head) {
	if (head == NULL || head->next == NULL) return head;
	ListNode* current = head->next;
	ListNode* prev = head;
	while (current) {
		if (prev == head) {
			prev->next = current->next;
			current->next = prev;
			ListNode *n = current;
			head = n;
			prev = prev->next;
			if (prev == NULL || prev->next == NULL) return head;
			current = prev->next;
		}
		if (prev == NULL || prev->next == NULL) return head;
		ListNode *p = current;
		prev->next = current->next;
		ListNode *q = findPrev(prev, head);
		q->next = p;
		p->next = prev;
		prev = prev->next;
		if (prev == NULL) return head;
		current = prev->next;
	}
	return head;
}
