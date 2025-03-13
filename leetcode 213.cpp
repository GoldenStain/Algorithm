class Solution {
    public:
        int rob(vector<int>& nums) {
            int n = nums.size();
            if (n == 1)
                return nums[0];
            return std::max(dp(nums, 0, n - 2), dp(nums, 1, n - 1));
        }
        int dp(vector<int>& nums, int l, int r) {
            std::vector<vector<int>> dp(2, vector<int>{0, nums[l]});
            int now, prev;
            for (int i = l + 1; i <= r; i++) {
                now = i & 1, prev = now ^ 1;
                dp[now][1] = dp[prev][0] + nums[i];
                dp[now][0] = std::max(dp[prev][0], dp[prev][1]);
            }
            return max(dp[now][0], dp[now][1]);
        }
    };