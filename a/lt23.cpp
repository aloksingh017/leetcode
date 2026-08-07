/*
23. Merge k Sorted Lists

You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.

Example 1:
Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted linked list:
1->1->2->3->4->4->5->6

Example 2:
Input: lists = []
Output: []

Example 3:
Input: lists = [[]]
Output: []
 

Constraints:

k == lists.length
0 <= k <= 104
0 <= lists[i].length <= 500
-104 <= lists[i][j] <= 104
lists[i] is sorted in ascending order.
The sum of lists[i].length will not exceed 104.

Complexity

Each node is

inserted once
removed once

Heap size ≤ k.

Time

O(N log k)

Space

O(k)
 
*/

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size()==0) return NULL;
        priority_queue<pair<int,ListNode*>, vector<pair<int,ListNode*>>, greater<pair<int,ListNode*>>>pq;

        for(auto list:lists){
            if(list!=NULL)
                pq.push({list->val,list});
        }
        ListNode* dummy= new ListNode(-1);
        ListNode* tail= dummy;
        while(!pq.empty()){
            ListNode* temp=pq.top().second;
            pq.pop();
            if(temp->next!=NULL){
                pq.push({temp->next->val,temp->next});
            }
            tail->next=temp;
            tail=tail->next;
        }
        return dummy->next;
    }
};