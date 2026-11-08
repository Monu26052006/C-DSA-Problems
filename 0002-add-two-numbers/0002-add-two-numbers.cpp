/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        //3 variable
        ListNode* dummy = new ListNode(0); //to store the starting point of the result
        ListNode* curr = dummy; //helps us insert the new nodes into the result list
        int carry = 0; //carry the extra value when sum is greater than 9

        //continue until both lists are finished and no carry remains
        while(l1 !=nullptr || l2 !=NULL || carry){
            int sum = carry;
            if(l1!=nullptr){
                sum += l1->val;
                l1 = l1->next;
            }
            if(l2 !=nullptr){
                sum += l2->val;
                l2 = l2->next;
            }
            carry = sum /10; //carry for the next iteration;
            curr->next = new ListNode(sum%10); //extract the current digit and create a new node
            curr = curr->next;
        }
        return dummy->next;



    }
};