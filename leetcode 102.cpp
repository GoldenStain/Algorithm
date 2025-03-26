// BFS solution
class Solution {
   public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) {
            return vector<vector<int>>{};
        }
        vector<vector<int>> ans;
        queue<TreeNode*> q;
        q.push(root);
        while (q.size()) {
            int n = q.size();
            vector<int> tmp;
            for (int i = 1; i <= n; i++) {
                TreeNode* head = q.front();
                tmp.emplace_back(head->val);
                q.pop();
                if (head->left) q.push(head->left);
                if (head->right) q.push(head->right);
            }
            ans.emplace_back(std::move(tmp));
        }
        return ans;
    }
};