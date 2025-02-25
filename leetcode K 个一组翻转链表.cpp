class Solution {
   public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head) return head;
        int n = get_len(head);
        ListNode *dummy = new ListNode(-1, head), *cur = dummy;
        for (int now = 0; now + k <= n; now += k) {
            std::cout << now << std::endl;
            cur = onceReverse(cur, k);
        }
        return dummy->next;
    }

   private:
    int get_len(ListNode* head) {
        int n = 0;
        while (head) {
            n++;
            head = head->next;
        }
        return n;
    }
    ListNode* onceReverse(ListNode* d, int k) {
        ListNode *cur = d, *prev = nullptr;
        for (int i = 0; i <= k; i++) {
            ListNode* _next = cur->next;
            if (i > 1) {
                cur->next = prev;
            }
            prev = cur;
            cur = _next;
        }
        // 内部关系调整完毕，要调整和外部的链接关系
        ListNode* ans = d->next;
        ans->next = cur;
        d->next = prev;
        return ans;
    }
};