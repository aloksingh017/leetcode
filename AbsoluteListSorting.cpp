/*
Given a linked list, sorted in ascending order based on the absolute values of its data,i.e. negative values
 are considered as positive ones. Sort the linked list in ascending order according to the actual values, 
 and consider negative numbers as negative and positive numbers as positive.


*/



class Solution {

  public:
    Node* sortList(Node* head) {
        // Your Code Here
        Node* cur=head->next;
        Node* prev= head;
        
        while(cur!=NULL){
            if(prev->data>cur->data){
                prev->next=cur->next;
                cur->next=head;
                head=cur;
                cur=prev;
            }else{
                prev=cur;
            }
            cur=cur->next;
        }
        return head;
    }
};
