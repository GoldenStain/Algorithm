// slow way

class Solution {
    public:
        std::vector<vector<int>> ans;
        vector<vector<int>> combine(int n, int k) {
            vector<int> arr{};
            dfs(1, 0, n, k, arr);
            return ans;
        }
        void dfs(int now, int chosen, int n, int k, vector<int>& arr) {
            // 剪枝
            if (arr.size() + (n - now + 1) < k)
                return;

            if (now == n + 1 || chosen == k) {
                if (chosen == k)
                    ans.push_back(arr);
                return;
            }
            dfs(now + 1, chosen, n, k, arr);
            arr.push_back(now);
            dfs(now + 1, chosen + 1, n, k, arr);
            arr.pop_back();
        }
    };