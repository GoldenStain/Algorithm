class Solution {
    public:
        int rob(vector<int>& nums) {
            int n = nums.size();
            // 注意如果用{}，就不会被认为是列表初始化，会被当做一个initialize_list，用小括号才能匹配上构造函数
            vector<vector<int>> dp{2, vector<int>{0, nums[0]}};
            for(int i = 1; i < n; i++)
            {
                int idx = i % 2;
                dp[idx][1] = dp[idx^1][0] + nums[i];
                dp[idx][0] = std::max(dp[idx^1][0], dp[idx^1][1]);
            }
            n = (n-1)&1;
            return std::max(dp[n][1], dp[n][0]);
        }
    };