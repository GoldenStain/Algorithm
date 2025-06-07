// recursive solution
class Solution {
public:
  vector<int> lexicalOrder(int n) {
    std::vector<int> ans;
    auto dfs = [&](this auto &dfs, int cur, int limit) {
      if (cur > limit)
        return;
      ans.emplace_back(cur);
      for (int i = 0; i <= 9; i++) {
        dfs(cur * 10 + i, limit);
      }
    };
    // 分别进行搜索
    for (int i = 1; i <= 9; i++)
      dfs(i, n);
    return ans;
  }
};
