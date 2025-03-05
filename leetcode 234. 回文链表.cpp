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