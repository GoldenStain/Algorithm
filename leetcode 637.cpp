// BFS solution
class Solution {
    public:
     vector<double> averageOfLevels(TreeNode *root) {
         if (!root) {
             return vector<double>{};
         }
         queue<TreeNode *> q;
         vector<double> ans;
         q.push(root);
         while (q.size()) {
             TreeNode *head = q.front();
             int n = q.size(), cnt = 1;
             ans.push_back(1.0 * head->val);
             q.pop();
             if (head->left) q.push(head->left);
             if (head->right) q.push(head->right);
             for (int i = 1; i < n; i++) {
                 head = q.front();
                 q.pop();
                 ans.back() += head->val;
                 cnt++;
                 if (head->left) q.push(head->left);
                 if (head->right) q.push(head->right);
             }
             ans.back() /= cnt;
         }
         return ans;
     }
 };