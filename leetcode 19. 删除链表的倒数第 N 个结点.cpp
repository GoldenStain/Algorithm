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
        ListNode* removeNthFromEnd(ListNode* head, int n) {
            ListNode* dummy = new ListNode(-1, head);
            std::stack<ListNode*> stk;
            if (!head)
                return head;
            ListNode *cur = dummy;
            while(cur) {
                stk.push(cur);
                cur = cur->next;
            }
            for(int i = 1; i <= n; i++)
                stk.pop();
            ListNode* t = stk.top();
            t->next = t->next?t->next->next:nullptr;
            return dummy->next;
        }
    };

// solution 2
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
        ListNode* removeNthFromEnd(ListNode* head, int n) {
            if (!head)
                return head;
            ListNode *dummy = new ListNode(-1, head);
            ListNode *slow = dummy, *fast = head;
            for(int i = 0; i < n; i++)
                fast = fast->next;
            while(fast) {
                slow = slow->next;
                fast = fast->next;
            }
            slow->next = slow->next->next;
            return dummy->next;
        }
    };    