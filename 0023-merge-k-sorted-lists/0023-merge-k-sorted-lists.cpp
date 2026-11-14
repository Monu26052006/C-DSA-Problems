
class Solution {
public:
    struct compare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {

        priority_queue<ListNode*, vector<ListNode*>, compare> pq;

        // Insert heads
        for(ListNode* head : lists) {
            if(head != nullptr) {
                pq.push(head);
            }
        }

        ListNode dummy(-1);
        ListNode* tail = &dummy;

        while(!pq.empty()) {

            ListNode* smallest = pq.top();
            pq.pop();

            tail->next = smallest;
            tail = smallest;

            if(smallest->next != nullptr) {
                pq.push(smallest->next);
            }
        }

        tail->next = nullptr;

        return dummy.next;
    }
};
