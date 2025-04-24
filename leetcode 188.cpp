class Solution {
public:
  int maxProfit(int k, vector<int> &prices) {
    int n = prices.size();
    // dp[n & 1][0][k] 手上没有股票，第n天，已经进行了k次交易
    std::vector<std::vector<std::vector<int>>> dp(
        2,
        std::vector<std::vector<int>>(2, std::vector<int>(k + 1, -0x3f3f3f3f)));
    int cnt = 1, ans = 0;
    dp[0][0][0] = 0;
    dp[0][1][0] = -prices[0];
    ans = std::max(dp[0][0][0], dp[0][1][0]);
    for (int i = 1; i < n; i++) {
      cnt = i & 1;
      for (int j = 0; j <= k; j++) {
        dp[cnt][0][j] = dp[cnt ^ 1][0][j];
        if (j)
          dp[cnt][0][j] =
              std::max(dp[cnt ^ 1][1][j - 1] + prices[i], dp[cnt][0][j]);
        dp[cnt][1][j] =
            std::max(dp[cnt ^ 1][1][j], dp[cnt ^ 1][0][j] - prices[i]);
        ans = std::max(std::max(dp[cnt][0][j], dp[cnt][1][j]), ans);
      }
    }
    return ans;
  }
};