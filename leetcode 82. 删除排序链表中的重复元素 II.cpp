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

// solution
class Solution {
   public:
    ListNode *deleteDuplicates(ListNode *head) {
        ListNode *dummy = new ListNode(-101, nullptr);
        int cnt = 0;
        ListNode *now = dummy, *prev = dummy;
        while (head) {
            if (head->val == prev->val)
                cnt++;
            else {
                if (cnt == 1) {
                    now->next = new ListNode(prev->val, nullptr);
                    now = now->next;
                }
                cnt = 1;
            }
            prev = head;
            head = head->next;
        }
        if (cnt == 1) now->next = new ListNode(prev->val, nullptr);
        return dummy->next;
    }
};

// wrong code
class Solution {
   public:
    ListNode *deleteDuplicates(ListNode *head) {
        ListNode *dummy = new ListNode(-101, head);
        int cnt = 0;
        ListNode *now = dummy, *prev = dummy;
        while (head) {
            if (head->val == prev->val)
                cnt++;
            else {
                if (cnt == 1) {
                    now->next = prev;
                    now = now->next;
                }
                cnt = 1;
            }
            prev = head;
            head = head->next;
        }
        if (cnt == 1) now->next = prev;
        return dummy->next;
    }
};

// improved wrong code, which is right
class Solution {
   public:
    ListNode *deleteDuplicates(ListNode *head) {
        ListNode *dummy = new ListNode(-101, head);
        int cnt = 0;
        ListNode *now = dummy, *prev = dummy;
        while (head) {
            if (head->val == prev->val)
                cnt++;
            else {
                if (cnt == 1) {
                    now->next = prev;
                    now = now->next;
                }
                cnt = 1;
            }
            prev = head;
            head = head->next;
        }
        if (cnt == 1) now->next = prev, now = now->next;
        now->next = nullptr;
        return dummy->next;
    }
};

// improved official solution with delete operation
class Solution {
   public:
    ListNode *deleteDuplicates(ListNode *head) {
        ListNode *dummy = new ListNode(-101, head);
        ListNode *cur = dummy;
        // 后面不到两个就不用判断了
        while (cur->next && cur->next->next) {
            if (cur->next->val == cur->next->next->val) {
                int x = cur->next->val;
                while (cur->next && cur->next->val == x) {
                    ListNode *l = cur->next;
                    cur->next = cur->next->next;
                    delete l;
                }
            } else
                cur = cur->next;
        }
        return dummy->next;
    }
};

// improved my solution
// 像支持删除就得把我的思路从向前看改成向后看，改成向后看的话，就跟官方题解一模一样了