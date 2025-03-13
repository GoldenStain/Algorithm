/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    using PII = pair<int, int>;
public:
    int rob(TreeNode* root) {
        if (!root)
            return 0;
        PII ans = dfs(root);
        return std::max(ans.first, ans.second);
    }
    PII dfs(TreeNode *root) {
        if (!root)
            return std::make_pair(0, 0);
        int buy = root->val, no = 0;
        auto l = dfs(root->left), r = dfs(root->right);
        buy += l.second + r.second;
        no = max(l.first, l.second) + max(r.first, r.second);
        return std::make_pair(buy, no);
    }
};