// solution 1
class Solution {
   public:
    TreeNode *sortedListToBST(ListNode *head) {
        if (!head) {
            return nullptr;
        }
        return buildTree(head, nullptr);
    }
    // [left, right) 区间
    TreeNode *buildTree(ListNode *left, ListNode *right) {
        if (left == right) {
            return nullptr;
        }
        ListNode *mid = getMid(left, right);
        // mid点已经在此处创建，所以后续的left和right函数不再需要考虑这个点
        TreeNode *now = new TreeNode(mid->val);
        // [left, mid)区间
        now->left = buildTree(left, mid);
        // [mid->next, right)区间
        now->right = buildTree(mid->next, right);
        return now;
    }
    ListNode *getMid(ListNode *left, ListNode *right) {
        ListNode *slow = left, *fast = left;
        while (fast != right && fast->next != right) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
};

// solution 2
class Solution {
   public:
    TreeNode *sortedListToBST(ListNode *head) {
        if (!head) {
            return nullptr;
        }
        int len = getLen(head);
        return buildTree(head, 1, len);
    }
    int getLen(ListNode *head) {
        int cnt = 0;
        while (head) {
            cnt++;
            head = head->next;
        }
        return cnt;
    }
    // [left, right]闭区间
    TreeNode *buildTree(ListNode *&head, int left, int right) {
        if (left > right) {
            return nullptr;
        }
        int mid = (left + right) >> 1;
        TreeNode *now = new TreeNode();
        now->left = buildTree(head, left, mid - 1);
        now->val = head->val;
        head = head->next;
        now->right = buildTree(head, mid + 1, right);
        return now;
    }
};