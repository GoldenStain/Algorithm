// solution 1
class Solution {
    public:
     TreeNode* sortedListToBST(ListNode* head) {
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
         TreeNode *now = new TreeNode(mid->val);
         now->left = buildTree(left, mid);
         now->right = buildTree(mid->next, right);
         return now;
     }
     ListNode *getMid(ListNode *left, ListNode *right) {
         ListNode *slow = left, *fast = left;
         while(fast != right && fast->next != right) {
             fast = fast->next->next;
             slow = slow->next;
         }
         return slow;
     }
 };