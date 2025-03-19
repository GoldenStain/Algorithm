// wrong dfs
class Solution {
   public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        dfs(n, ans, "", false);
        return ans;
    }
    void dfs(int now, vector<string>& arr, string s, bool flag) {
        if (flag) s.append(")");
        if (now == 0) {
            arr.push_back(s);
            return;
        }
        s.append("(");
        dfs(now - 1, arr, s, true);
        dfs(now - 1, arr, s + ")", false);
    }
};

// dfs1
class Solution {
   public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string cur;
        dfs(ans, cur, 0, 0, n);
        return ans;
    }
    void dfs(vector<string>& ans, string cur, int left, int right, int n) {
        if (cur.size() == 2 * n) {
            ans.emplace_back(cur);
            return;
        }
        if (left < n) {
            cur.append(1, '(');
            dfs(ans, cur, left + 1, right, n);
            cur.pop_back();
        }
        // 原来是手动控制右括号放在那里，我们可以让递归来代替我们做这个选择
        // 在当前层走向这一分支，就对应在最后面放上对应当前左括号的右括号
        // 在最后一层走向这一分支，就对应放完左括号立马放右括号.
        if (right < left) {
            cur.append(1, ')');
            dfs(ans, cur, left, right + 1, n);
            cur.pop_back();
        }
    }
};

// Memorization Search
class Solution {
    vector<shared_ptr<vector<string>>> dp;
   public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string cur;
        dp.assign(n, nullptr);
        return *dfs(n);
    }
    
    shared_ptr<vector<string>> dfs(int n) {
        if (dp[n]) 
            return dp[n];
        auto res = std::make_shared<vector<string>>();
        if (n == 0) {
            res->emplace_back("");
            dp[0] = res;
            return res;
        }
        for (int i = 0; i < n; i++) {
            auto left = dfs(i), right = dfs(n - i - 1);
            for (auto &li: *left) { // 因为是指针，要记得解引用
                for (auto &ri: *right) {
                    res->emplace_back("(" + li + ")" + ri);
                }
            }
        }
        dp[n] = res;
        return res;
    }
};