/* Structure of a Linked List Node
class Node
{
    int data;
    Node next;
    Node(int d) {
       data = d;
       next = nullptr;
    }
};*/
class Solution {
  public:
  
    ListNode* merge(ListNode* l1, ListNode* l2){
        ListNode* dummy = new ListNode(-1);
        ListNode* tail = dummy;
        while(l1 && l2){
            if(l1->val <= l2->val){
                tail->next = l1;
                l1 = l1->next;
            }
            else{
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
            
            
        }
        if(l1) tail->next = l1;
        if(l2) tail->next = l2;
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
    ListNode* sortList(ListNode* head) {
        // code here
        if(head==NULL || head->next==NULL) return head;
        //find middle
        ListNode* slow = head;
        ListNode* fast = head->next;
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        
        //divide into two half
        ListNode* second = slow->next;
        slow->next = nullptr;
        
        //recursively
        ListNode* left = sortList(head);
        ListNode* right = sortList(second);
        
        return merge(left, right);
    }
};