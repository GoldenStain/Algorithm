class Solution {
    public:
        ListNode *front;
        bool isPalindrome(ListNode* head) {
            front = head;
            return check(head);
        }
        // 注意front不能作为函数的参数传递，否则各层递归之间的front互不影响，我们的修改就无效了。
        bool check(ListNode* now) {
            if (now) {
                // 接住下一层的结果，往上抛
                if (!check(now->next))
                    return false;
                if (now->val != front->val)
                    return false;
                front = front->next;
            }
            return true;
        }
    };

// my complicated solution
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
        bool isPalindrome(ListNode* head) {
            if (!head || !head->next)
                return true;
            if (!head->next->next)
                return head->val == head->next->val;            
            ListNode *tmp_next = head;
            ListNode *mid = getMiddle(head, tmp_next);
            ListNode *another = tmp_next;
            while(another) {
                if (mid->val != another->val)
                    return false;
                // cout << mid->val << " " << another->val << endl;
                mid = mid->next;
                another = another->next;
            }
            return true;
        }
    private:
        ListNode* getMiddle(ListNode *head, ListNode* &tmp_next) {
            ListNode *prev = nullptr;
            ListNode *slow = head, *fast = head;
            while(fast->next && fast->next->next) {
                fast = fast->next->next;
                tmp_next = slow->next;
                slow->next = prev;
                prev = slow;
                slow = tmp_next;
            }
            tmp_next = slow->next;
            // cout << tmp_next->val << endl;
            // 最后一个点没有反向链接，需要手动处理。
            slow->next = prev;
            if (fast->next == nullptr)
                slow = slow->next;
            return slow;
        }
    };