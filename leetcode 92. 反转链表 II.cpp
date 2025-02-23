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
        ListNode* reverseBetween(ListNode* head, int left, int right) {
            if (!head)
                return head;
            ListNode *dummy = new ListNode(0, head);
            int cnt = 0;ListNode *now, *prev;
            ListNode *p;
            for(now = dummy, prev = nullptr;cnt <= right;cnt++) {
                ListNode *_next = now->next;
                if (cnt == left - 1)
                    p = now;
                if (cnt > left && cnt <= right) {
                    now->next = prev;
                }
                // finally
                prev = now;
                now = _next;
            }
            p->next->next = now;
            p->next = prev;
            return dummy->next;
        }
    };