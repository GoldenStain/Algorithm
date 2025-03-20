class Solution {
    int ans = INT_MIN;

   public:
    int maxPathSum(TreeNode *root) {
        dfs(root);
        return ans;
    }
    int dfs(TreeNode* root) {
        if (!root) {
            return INT_MIN;
        }
        // 这里对叶子节点的特判可以去掉，因为我们的通解公式能够覆盖这个case，在叶子结点，l_max和r_max都是0.
        if (!root->left && !root->right) {
            ans = std::max(ans, root->val);
            return root->val;
        }
        int l_max = 0, r_max = 0;
        r_max = std::max(0, dfs(root->right));
        l_max = std::max(0, dfs(root->left));
        // 这里如果l_max和r_max都是0，就说明两边都是负数，都不走
        ans = std::max(ans, r_max + root->val + l_max);
        return std::max(l_max, r_max) + root->val;
    }
};
