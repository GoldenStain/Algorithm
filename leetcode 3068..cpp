// solution 1
class Solution {
public:
  long long maximumValueSum(vector<int> &nums, int k,
                            vector<vector<int>> &edges) {
    int n = nums.size();
    vector<int> diffs(n);
    long long res = 0ll;
    for (int i = 0; i < n; i++) {
      diffs[i] = (nums[i] ^ k) - nums[i];
      res += nums[i];
    }
    std::sort(diffs.begin(), diffs.end(), [](int a, int b) { return a > b; });
    // 注意i+=2，而不是i++
    for (int i = 0; i + 1 < n; i += 2) {
      res += std::max(0, diffs[i] + diffs[i + 1]);
    }
    return res;
  }
};

// solution 2
// 状态设计很棒，值得学习，但是在这道题上运行的时候效率明显比不过其他两种解法
// 注意这个解法的状态定义当中,f[u][0]和f[u][1]表示的都是子树上除了u本身的和，这样子方便我们进行状态转移
// 这个状态设计的精髓在于，我们在对子树v进行dp的时候，因为这个dp是从下到上的，我们不可能知道v和父节点u之间有没有进行异或
// 因此我们直接把节点v本身排除在状态设计之外，等到了用v来求u（往上走）的时候，再去决定u和v之间是否进行操作
class Solution {
public:
  long long maximumValueSum(vector<int> &nums, int k,
                            vector<vector<int>> &edges) {
    int n = nums.size();
    vector es(n, vector<int>{});
    for (auto &ei : edges) {
      int a = ei[0], b = ei[1];
      es[a].push_back(b);
      es[b].push_back(a);
    }
    std::function<std::pair<long long, long long>(int, int)> dfs =
        [&](int u, int fa) -> std::pair<long long, long long> {
      long long f0 = 0, f1 = LLONG_MIN;
      for (int ei : es[u]) {
        if (ei == fa) {
          continue;
        }
        auto [r0, r1] = dfs(ei, u);
        // 因为dp公式里面，等式的右边都是上一轮的值，所以这里我们要用一个中间变量暂存一下。
        long long t = std::max(f1 + r0, f0 + r1);
        f0 = std::max(f0 + r0, f1 + r1);
        f1 = t;
      }
      return std::make_pair(std::max(f0 + nums[u], f1 + (nums[u] ^ k)),
                            std::max(f0 + (nums[u] ^ k), f1 + nums[u]));
    };
    return dfs(0, -1).first;
  }
};

// 状态设计见官方题解解法3
class Solution {
public:
  long long maximumValueSum(vector<int> &nums, int k,
                            vector<vector<int>> &edges) {
    int n = nums.size();
    vector dp(2, vector<long long>(2, LLONG_MIN));
    dp[0][0] = nums[0];
    // 一开始写错了,给dp[0][1]赋值无穷小，要注意这道题的状态设计下，dp[i][1]本身是有物理意义的合法值，只不过最后的答案必须是dp[i][0]而已
    // 二者都是合法的符合物理意义的值，不能给dp[0][1]赋非法值
    dp[0][1] = nums[0] ^ k;
    int idx = 0;
    for (int i = 1; i < n; i++) {
      idx = i & 1;
      dp[idx][0] =
          std::max(dp[idx ^ 1][0] + nums[i], dp[idx ^ 1][1] + (nums[i] ^ k));
      dp[idx][1] =
          std::max(dp[idx ^ 1][1] + nums[i], dp[idx ^ 1][0] + (nums[i] ^ k));
    }
    return dp[idx][0];
  }
};