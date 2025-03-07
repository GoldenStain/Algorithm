/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *  
    TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    public:
        bool isSymmetric(TreeNode* root) {
            if (!root)
                return true;
            return twoSymmetric(root->left, root->right);
        }
        bool twoSymmetric(TreeNode *a, TreeNode *b) {
            if (!a && !b)
                return true;
            if (!a || !b)
                return false;
            // 对称条件，本身value相等，各自左右互成镜像。
            return (a->val == b->val) && twoSymmetric(a->right, b->left) && twoSymmetric(a->left, b->right);
        }
    };

// 迭代做法
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
        bool isSymmetric(TreeNode* root) {
            if (!root)
                return true;
            std::queue<TreeNode*> q;
            q.push(root);q.push(root);
            while(q.size()) {
                auto a = q.front();
                q.pop();
                auto b = q.front();
                q.pop();
                if (!a && !b)
                    continue;
                if (!a || !b)
                    return false; 
                if (a->val != b->val)
                    return false;
                q.push(a->left);
                q.push(b->right);
                q.push(a->right);
                q.push(b->left);
            }
            return true;
        }
    };