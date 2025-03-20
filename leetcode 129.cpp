class Solution {
    typedef long long ll;

   public:
    ll ans = 0;
    int sumNumbers(TreeNode* root) {
        dfs(root, 0ll);
        // 每个叶子节点会走到两次nullptr，会导致每个值被加两次
        return ans / 2;
    }
    void dfs(TreeNode* root, ll value) {
        if (!root) {
            ans += value;
            return;
        }
        dfs(root->left, value * 10 + root->val);
        dfs(root->right, value * 10 + root->val);
    }
};

// right dfs 1
class Solution {
    typedef long long ll;

   public:
    ll ans = 0;
    int sumNumbers(TreeNode* root) {
        dfs(root, 0ll);
        return ans;
    }
    void dfs(TreeNode* root, ll value) {
        if (!root) {
            return;
        }
        if (!root->left && !root->right) {
            ans += value * 10 + root->val;
            return;
        }
        dfs(root->left, value * 10 + root->val);
        dfs(root->right, value * 10 + root->val);
    }
};

// right dfs 2
class Solution {
    typedef long long ll;

   public:
    int sumNumbers(TreeNode* root) { return dfs(root, 0ll); }
    ll dfs(TreeNode* root, ll value) {
        if (!root) {
            return 0ll;
        }
        ll sum_now = value * 10 + root->val;
        if (!root->left && !root->right) {
            return sum_now;
        }
        return dfs(root->left, sum_now) + dfs(root->right, sum_now);
    }
};

// bfs
class Solution {
    typedef long long ll;

   public:
    int sumNumbers(TreeNode* root) {
        queue<std::pair<TreeNode*, ll>> q;
        q.push({root, root->val});
        ll ans = 0ll;
        while (q.size()) {
            auto tmp = q.front();
            q.pop();
            auto f = tmp.first;
            auto s = tmp.second;
            if (!f->left && !f->right) {
                ans += s;
            } else {
                TreeNode *l = f->left, *r = f->right;
                if (l) q.push({l, s * 10 + l->val});
                if (r) q.push({r, s * 10 + r->val});
            }
        }
        return ans;
    }
};