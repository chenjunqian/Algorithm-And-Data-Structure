//
//  Solution.h
//  DeleteNodeInLinkedList
//
//  Created by BigHead_Chen on 7/18/15.
//  Copyright (c) 2015 Eason. All rights reserved.
//

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void deleteNode(ListNode* node) {
        if(node == NULL || node->next == NULL)
            return;
        ListNode *tmp = node->next;
        node->val = tmp->val;
        node->next = tmp->next;
        delete tmp;
    }
};