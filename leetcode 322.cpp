class Solution {
    public:
     int coinChange(vector<int>& coins, int amount) {
         int n = coins.size();
         vector<int> dp(amount + 1, 1e5);
         dp[0] = 0;
         for (int i = 0; i < n; i++) {
             for (int j = coins[i]; j <= amount; j++) {
                 dp[j] = std::min(dp[j - coins[i]] + 1, dp[j]);
             }
         }
         return dp[amount]==1e5?-1:dp[amount];
     }
 };