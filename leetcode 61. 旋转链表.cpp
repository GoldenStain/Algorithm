// solution
class Solution {
    public:
        ListNode* rotateRight(ListNode* head, int k) {
            if (!head)
                return head;
            ListNode *dummy = new ListNode(-101, head), *cur = head;
            int n = 0;
            ListNode *end;
            while(cur) {
                n++;
                if (cur->next == nullptr)
                    end = cur;
                cur = cur->next;
            }
            k %= n;
            // 我们会移动到后k个，然后重新组织链表，如果k现在是0，就不存在所谓的后k个，我们就会段错误，所以这里特判一下，直接返回
            if (!k)
                return head;
            ListNode* mark = head;
            cur = head;
            for(int i = 1; i <= n - k; i++) {
                ListNode *_next = cur->next;
                if (i == n - k)
                    cur->next = nullptr;
                cur = _next;
            }
            dummy->next = cur;
            end->next = head;
            return dummy->next;
        }
    };

// official solution

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
        ListNode* rotateRight(ListNode* head, int k) {
            if (!head || !head->next)
                return head;
            int n = 1;
            ListNode *cur = head;
            // 因为我们要把最后一个节点连接成环，这里就不能跳到nullptr了。
            while(cur->next) {
                n++;
                cur = cur->next;
            }
            k %= n;
            if (!k)
                return head;
            cur->next = head;
            for(int i = 1; i <= n - k; i++) {
                cur = cur->next;
            }
            ListNode* ans = cur->next;
            cur->next = nullptr;
            return ans;
        }
    };