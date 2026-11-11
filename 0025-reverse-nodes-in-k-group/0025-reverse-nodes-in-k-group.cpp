
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {

        if (head == nullptr || k == 1)
            return head;

        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* groupPrev = dummy;

        while (true) {

            // Step 1: Find kth node
            ListNode* kth = groupPrev;

            for (int i = 0; i < k && kth != nullptr; i++) {
                kth = kth->next;
            }

            // Not enough nodes
            if (kth == nullptr)
                break;

            // Step 2: Store next group
            ListNode* groupNext = kth->next;

            // Step 3: Reverse current group
            ListNode* prev = groupNext;
            ListNode* curr = groupPrev->next;

            while (curr != groupNext) {

                ListNode* nextNode = curr->next;

                curr->next = prev;

                prev = curr;
                curr = nextNode;
            }

            // Step 4: Connect reversed group
            ListNode* temp = groupPrev->next;

            groupPrev->next = kth;

            groupPrev = temp;
        }

        return dummy->next;
    }
};
