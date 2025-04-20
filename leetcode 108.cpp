class Solution {
public:
  TreeNode *sortedArrayToBST(vector<int> &nums) {
    int n = nums.size();
    return buildTree(nums, 0, n - 1);
  }
  TreeNode *buildTree(vector<int> &nums, int l, int r) {
    if (l > r)
      return nullptr;
    int mid = (l + r) >> 1;
    TreeNode *new_node = new TreeNode(nums[mid]);
    new_node->left = buildTree(nums, l, mid - 1);
    new_node->right = buildTree(nums, mid + 1, r);
    return new_node;
  }
};