// dfs
class Solution {
    public:
        std::vector<vector<int>> ans;
        vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
            int n = candidates.size();
            std::vector<int> arr;
            std::sort(candidates.begin(), candidates.end(),
                      [](int a, int b) { return a > b; });
            dfs(candidates, 0, n, arr, target);
            return ans;
        }
        void dfs(vector<int>& candidates, int now, int len, vector<int>& arr,
                 int target) {
            if (!target) {
                ans.emplace_back(arr);
                return;
            }
            if (now == len)
                return;
            // 不选，或者选完了当前这个，开始选下一个
            dfs(candidates, now + 1, len, arr, target);
            // 选
            if (candidates[now] <= target) {
                arr.emplace_back(candidates[now]);
                dfs(candidates, now, len, arr, target - candidates[now]);
                arr.pop_back();
            }
        }
    };

// 完全背包
class Solution {
    public:
        vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
            // 创建动态数组 dp，用于存储所有可能的组合
            vector<vector<vector<int>>> dp(target + 1);
    
            // 初始化 dp[0]，表示目标和为 0 的初始情况
            dp[0] = {{}};
    
            for (int i = 0; i < candidates.size(); i++) {
                for (int j = candidates[i]; j <= target; j++) {
                    for (auto& group : dp[j - candidates[i]]) {
                        vector<int> newGroup = group;      // 复制当前组合
                        newGroup.push_back(candidates[i]); // 添加新的候选数
                        dp[j].push_back(newGroup);         // 添加到当前目标和的组合
                    }
                }
            }
    
            return dp[target];
        }
    };