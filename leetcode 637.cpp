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

// optimized BFS solution
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
            int n = q.size();
            ans.push_back(0.f);
            for (int i = 1; i <= n; i++) {
                head = q.front();
                q.pop();
                ans.back() += head->val;
                if (head->left) q.push(head->left);
                if (head->right) q.push(head->right);
            }
            ans.back() /= n;
        }
        return ans;
    }
};

// DFS solution
// 这份代码一开始用的不是(double)来转浮点数，而是用的1.f*int_val，但是这样交上去会出问题
// 因为用1.f*int_val只能得到float，float精度不够，再转换到double经过缩放可能就会出错。
class Solution {
   public:
    vector<double> averageOfLevels(TreeNode *root) {
        if (!root) {
            return vector<double>{};
        }
        vector<double> ans;
        vector<int> size;
        dfs(root, 1, ans, size);
        for (int i = 0; i < ans.size(); i++) ans[i] /= (double)size[i];
        return ans;
    }
    void dfs(TreeNode *root, int depth, vector<double> &ans,
             vector<int> &size) {
        if (!root) {
            return;
        }
        if (ans.size() < depth) {
            ans.emplace_back((double)root->val);
            size.emplace_back(1);
        } else {
            // 这里的下标从0开始，所以要减去一
            ans[depth - 1] += root->val;
            size[depth - 1]++;
        }
        dfs(root->left, depth + 1, ans, size);
        dfs(root->right, depth + 1, ans, size);
    }
};