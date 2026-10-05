/*
25. Reverse Nodes in k-Group

Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.
k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.
You may not alter the values in the list's nodes, only nodes themselves may be changed.

Example 1:

Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]

Example 2:

Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]

Example 3:

Input: head = [1,2,3,4,5], k = 1
Output: [1,2,3,4,5]
 

Constraints:

The number of nodes in the list is n.
1 <= n <= 5000
0 <= Node.val <= 999
1 <= k <= n
*/


ListNode* getK(ListNode* temp,int k){
        k--;
        while(temp && k>0){
            k--;
            temp=temp->next;
        }
        return temp;
    }
    ListNode* reverse(ListNode* head){
        ListNode* cur=head;
        ListNode* prev=NULL;
        ListNode* next=head;
        while(cur){
            next=cur->next;
            cur->next=prev;
            prev=cur;
            cur=next;
        }
        return prev;
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* temp=head;
        ListNode* prev=NULL;

        while(temp){
            ListNode* kthNode= getK(temp,k);
            if(kthNode==NULL){
                if(prev){
                    prev->next=temp;

                }
                break;
            }
            ListNode* nextNode= kthNode->next;
            kthNode->next=NULL;
            reverse(temp);
            if(temp==head){
                head=kthNode;
            }else{
                prev->next=kthNode;
            }
            prev=temp;
            temp=nextNode;
        }
        return head;
    }