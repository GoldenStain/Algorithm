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

// iterative solution
class Solution {
public:
  vector<int> lexicalOrder(int n) {
    std::vector<int> ans;
    for (int i = 0, j = 1; i < n; i++) {
      ans.emplace_back(j);
      if (j * 10 <= n)
        j *= 10; // 保持字典序最小的方法就是往后加零
      else {
        while (j + 1 > n || j % 10 == 9) { // 手动模拟回溯过程
          j /= 10;
        }
        j++;
      }
    }
    return ans;
  }
};