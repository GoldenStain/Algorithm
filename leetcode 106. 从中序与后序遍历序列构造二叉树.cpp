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
        using VecInt = vector<int>;
        TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
            int n = inorder.size();
            for (int i = 0; i < n; i++)
                pos_table[inorder[i]] = i;
            return work(inorder, postorder, 0, n-1, 0, n-1);
        }
    private:
        unordered_map<int, int> pos_table;
        TreeNode* work(VecInt& in, VecInt& post, int in_l, int in_r, int post_l, int post_r) {
            if (in_l > in_r)
                return nullptr;
            TreeNode* res = new TreeNode(post[post_r]);
            int root_in = pos_table[post[post_r]];
            int len_l = root_in - in_l, len_r = in_r - root_in;
            res->left = work(in, post, in_l, root_in - 1, post_l, post_l + len_l - 1);
            res->right = work(in, post, root_in +1, in_r, post_r - len_r, post_r - 1);
            return res;
        }
    };