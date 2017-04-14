//
//  Algo_List.hpp
//  Grindstone
//
//  Created by sphota on 8/12/16.
//  Copyright © 2016 Intellex. All rights reserved.
//

#ifndef Algo_List_hpp
#define Algo_List_hpp

#include "include.h"

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

ListNode* plusOne(ListNode* head);
ListNode* insertionSortList(ListNode* head);

#endif /* Algo_List_hpp */
