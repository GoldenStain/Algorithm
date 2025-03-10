// 树上翻转链表

class Solution {
   public:
    TreeNode* preNode = nullptr;
    void flatten(TreeNode* root) {
        if (!root) return;
        flatten(root->right);
        flatten(root->left);
        // 要记得把root->left设置为nullptr.
        root->left = nullptr;
        root->right = preNode;
        preNode = root;
    }
};

// 空间复杂度O(1)

class Solution {
   public:
    void flatten(TreeNode* root) {
        if (!root) return;
        TreeNode* cur = root;
        while (cur) {
            if (cur->left) {
                TreeNode* next = cur->left;
                TreeNode* p = next;
                while (p->right) p = p->right;
                if (p) p->right = cur->right;
                // 同样要记得断开左边的链接
                cur->left = nullptr;
                cur->right = next;
            }

            cur = cur->right;
        }
    }
};