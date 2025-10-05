class Solution {
    public:
     int countNodes(TreeNode *root) {
         if (!root)
             return 0;
         int depth = cnt(root) - 1; // 从0开始
         int l = (1 << depth), r = (1 << (depth + 1)) - 1;
         while (l < r) {
             int mid = (l + r + 1) >> 1;
             if (check(mid, root, depth)) {
                 l = mid;
             }
             else 
                 r = mid - 1;
         }
         return l;
     }
     int cnt(TreeNode *root) {
         if (!root) 
             return 0;
         return 1 + cnt(root->left);
     }
     bool check(int x, TreeNode* root, int depth) {
         TreeNode* cur = root;
         int bit = 1 << (depth - 1); // 最高位对应根节点，固定是1，不需要检查（如果想要强行保持行为一致，可以在root头上增加一个dummy_root.）
         // 这里不用担心depth传进来是0，导致左移一个负数产生未定义行为，因为当depth=0的时候，二分左右边界相等，会直接退出
         while(cur && bit) {
             if (bit & x) 
                 cur = cur->right;
             else 
                 cur = cur->left;
             bit >>= 1;
         }
         return cur != nullptr;
     }
 };