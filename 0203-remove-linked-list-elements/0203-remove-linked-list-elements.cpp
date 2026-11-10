class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {

        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* temp = dummy;

        while (temp->next != NULL) {

            if (temp->next->val == val) {

                ListNode* delNode = temp->next;

                temp->next = delNode->next;

                delete delNode;
            }
            else {
                temp = temp->next;
            }
        }

        head = dummy->next;
        delete dummy;

        return head;
    }
};