class Solution {
public:
  int minDistance(vector<int> &houses, int k) {
    int n = houses.size();
    std::sort(houses.begin(), houses.end());
    // 预处理cost数组, cost[l][r]表示，如果这个邮箱负责[l,
    // r]的房子，那么产生的代价是多少
    vector cost(n, vector<int>(n + 1, 0));
    // cost[l][r] = cost[l + 1][r - 1] + dist(l, r)
    // 这里循环顺序有两种写法：一种是外围枚举区间长度，内部枚举区间起点。
    // 第二种是根据递推公式，观察出哪些值需要先计算出来，然后再去计算
    for (int i = n - 1; ~i; i--)
      for (int j = i + 1; j < n; j++)
        cost[i][j] = (cost[i + 1][j - 1] + houses[j] - houses[i]);
    // 实际dp
    // dp[i][j]: 前i个房子，分配j个邮筒
    // 新放一个邮箱，假设它管理break_point + 1 ~ i 的所有房子
    // dp[i][j] = dp[break_point][j - 1] + cost(break_point, i)
    // 因为房子下标是从0开始的，所以0~i有i+1个房子
    vector dp(n, vector<int>(k + 1, 1e9));
    for (int i = 0; i < n; i++) {
      dp[i][1] = cost[0][i];
      for (int j = 2; j <= std::min(i + 1, k); j++) {
        for (int break_point = 0; break_point < i; break_point++) {
          dp[i][j] = std::min(dp[i][j], dp[break_point][j - 1] +
                                            cost[break_point + 1][i]);
        }
      }
    }
    return dp[n - 1][k];
  }
};
