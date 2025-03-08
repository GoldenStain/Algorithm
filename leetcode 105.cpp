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
    public:
        TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
            std::unordered_map<int, int> M;
            for(int i = 0; i < inorder.size(); i++) 
                M[inorder[i]] = i;
            int n = preorder.size();
            TreeNode *ans = solve(preorder, 0, n - 1, inorder, 0, n - 1, M);
            return ans;
        }
        TreeNode *solve(vector<int> &a, int la, int ra, vector<int> &b, int lb, int rb, unordered_map<int, int> &M) {
            if (la > ra)
                return nullptr;
            int root_now = a[la];
            int root_pos = M[root_now];
            int len_left = root_pos - lb, len_right = rb - root_pos;
            TreeNode *node = new TreeNode(root_now);
            node->left = solve(a, la + 1, la + len_left, b, lb, root_pos - 1, M);
            node->right = solve(a, ra - len_right + 1, ra, b, root_pos + 1, rb, M);
            return node;
        }
    };