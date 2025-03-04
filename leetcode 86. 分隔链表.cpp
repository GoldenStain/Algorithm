class Solution {
    public:
        ListNode* partition(ListNode* head, int x) {
            if (!head || !head->next)
                return head;
            ListNode *dummy1 = new ListNode(-1, nullptr), *dummy2 = new ListNode(-1, nullptr);
            ListNode *st = dummy1, *st2 = dummy2;
            while(head) {
                if (head->val < x) {
                    dummy1->next = head;
                    dummy1 = dummy1->next;
                }
                else {
                    dummy2->next = head;
                    dummy2 = dummy2->next;
                }
                head = head->next;
            }
            dummy1->next = st2->next;
            dummy2->next = nullptr;
            return st->next;
        }
    };