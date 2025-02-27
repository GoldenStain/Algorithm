// WA
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
        bool hasPathSum(TreeNode* root, int targetSum) {
            if (!root)
                return false;
            return check(root, targetSum, 0);
        }
        bool check(TreeNode *now, int targetSum, int sum) {
            if (!now)
                return sum == targetSum;
            return check(now->left, targetSum, sum + now->val) || check(now->right, targetSum, sum + now->val);
        }
    };

// my solution
class Solution {
    public:
        bool hasPathSum(TreeNode* root, int targetSum) {
            if (!root)
                return false;
            return check(root, targetSum, root->val);
        }
        bool check(TreeNode *now, int targetSum, int sum) {
            if (!now->left && !now->right)
                return sum == targetSum;
            bool ans = false;
            if (now->left)
                ans |= check(now->left, targetSum, sum + now->left->val);
            if (now->right)
                ans |= check(now->right, targetSum, sum + now->right->val);
            return ans;
        }
    };

// 正解DFS
class Solution {
    public:
        bool hasPathSum(TreeNode* root, int targetSum) {
            if (!root)
                return false;
            if(!root->left && !root->right)
                return root->val == targetSum;
            return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
        }
    };

// 正解BFS