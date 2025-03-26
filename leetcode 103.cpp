// wrong solution DFS
class Solution {
    public:
     vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
         if (!root) {
             return vector<vector<int>>{};
         }
         vector<vector<int>> ans;
         dfs(root, 1, ans);
         return ans;
     }
     void dfs(TreeNode *root, int depth, vector<vector<int>> &ans) {
         if (!root) {
             return;
         }
         if (ans.size() < depth) {
             ans.push_back(vector<int>{});
         }
         ans[depth - 1].push_back(root->val);
         // 当前是偶数，那么下一层是奇数，注意我们在这一层就能决定下一层的访问顺序，所以我们真正考虑的是下一层的奇偶性。
         if ((depth & 1) == 0) {
             dfs(root->left, depth + 1, ans);
             dfs(root->right, depth + 1, ans);
         }
         else {
             dfs(root->right, depth + 1, ans);
             dfs(root->left, depth + 1, ans);
         }
     }
 };