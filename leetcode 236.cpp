// 递归写法
class Solution {
   public:
    TreeNode* ans = nullptr;
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        findCommonAncestor(root, p, q);
        return ans;
    }
    // 这个函数的返回值表示：以root为根的子树当中，是否存在p或者q
    bool findCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return false;
        bool has_left = findCommonAncestor(root->left, p, q),
             has_right = findCommonAncestor(root->right, p, q);

        if ((has_left && has_right) ||
            ((root->val == p->val || root->val == q->val) &&
             (has_left || has_right))) {
            if (!ans)
                ans = root;
        }

        return has_left || has_right || root->val == p->val ||
               root->val == q->val;
    }
};

// 竞赛写法
class Solution {
    public:
        std::unordered_map<int, int> depth;
        std::unordered_map<int, TreeNode*> fa;
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            dfs(root, 1, nullptr);
            if (depth[p->val] < depth[q->val])
                std::swap(p, q);
            while(depth[p->val] > depth[q->val])
                p = fa[p->val];
            if (p == q)
                return q;
            while(fa[p->val] != fa[q->val])
                p = fa[p->val], q = fa[q->val];
            return fa[p->val];
        }
        void dfs(TreeNode* root, int d, TreeNode* f) {
            depth[root->val] = d;
            fa[root->val] = f;
            dfs(root->left, d + 1, root);
            dfs(root->right, d + 1, root);
        }
    };
