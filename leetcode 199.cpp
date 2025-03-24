// BFS solution
class Solution {
   public:
    vector<int> rightSideView(TreeNode* root) {
        if (!root) {
            return vector<int>{};
        }
        vector<int> ans;
        queue<TreeNode*> q;
        q.push(root);
        while (q.size()) {
            int n = q.size();
            TreeNode* head = q.front();
            ans.emplace_back(head->val);
            for (int i = 0; i < n; i++) {
                head = q.front();
                q.pop();
                if (head->right) q.push(head->right);
                if (head->left) q.push(head->left);
            }
        }
        return ans;
    }
};