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
    while (root) {
      TreeNode *root_left = root->left, *right_in_left = root_left;
      // 这个循环内部也是一种递归的逻辑
      while (right_in_left && right_in_left->right) {
        right_in_left = right_in_left->right;
      }
      if (right_in_left) {
        right_in_left->right = root->right;
        // 注意一下两行语句的顺序，千万不能搞反了
        root->right = root->left;
        root->left = nullptr;
      }
      root = root->right;
    }
  }
};