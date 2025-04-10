// 树上翻转链表

class Solution {
public:
  // lastNode是在回溯过程中，经过的上一个节点。
  TreeNode *lastNode = nullptr;
  void flatten(TreeNode *root) {
    if (!root)
      return;
    flatten(root->right);
    flatten(root->left);
    // 不需要显式地链接左右子树，因为在flatten(root->left)的时候，在子树最底部的节点，root->right
    // = lastNode已经完成了这个任务
    root->left = nullptr;
    root->right = lastNode;
    lastNode = root;
  }
};

// 空间复杂度O(1)

class Solution {
public:
  void flatten(TreeNode *root) {
    if (!root)
      return;
    TreeNode *cur = root;
    while (cur) {
      if (cur->left) {
        TreeNode *next = cur->left;
        TreeNode *p = next;
        while (p->right)
          p = p->right;
        if (p)
          p->right = cur->right;
        // 同样要记得断开左边的链接
        cur->left = nullptr;
        cur->right = next;
      }

      cur = cur->right;
    }
  }
};