class Solution {
public:
  int maximalRectangle(vector<vector<char>> &matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> ones(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (matrix[i][j] == '1') {
          ones[i][j] = (j == 0 ? 0 : ones[i][j - 1]) + 1;
        }
      }
    } // 预处理完毕
    std::vector<int> stk, up, down;
    int ans = 0;
    for (int j = 0; j < n; j++) {
      stk.clear();
      up.assign(m, -1);
      down.assign(m, m);
      for (int i = 0; i < m; i++) {
        while (stk.size() && ones[i][j] < ones[stk.back()][j]) {
          down[stk.back()] = i;
          stk.pop_back();
        }
        if (stk.size())
          up[i] = stk.back();
        stk.push_back(i);
      }
      for (int i = 0; i < m; i++) {
        int width = down[i] - up[i] - 1;
        ans = std::max(ans, width * ones[i][j]);
      }
    }
    return ans;
  }
};

// best solution
class Solution {
public:
  int maximalRectangle(vector<vector<char>> &matrix) {
    int m = matrix.size(), n = matrix[0].size();
    std::vector<int> heights(
        n, 0); // heights[i]: 当前行第i个位置（也就是第i列上，连续1的个数）
    heights.push_back(-1); // padding.
    int ans = 0;
    std::function<int()> computeArea = [&]() -> int {
      std::vector<int> stk;
      stk.push_back(-1); // padding
      int res = 0;
      for (int i = 0; i <= n; i++) {
        // 因为padding了，所以这里得是stk.size() > 1
        while (stk.size() > 1 && heights[stk.back()] >= heights[i]) {
          int h_now = heights[stk.back()];
          stk.pop_back();
          int left = stk.back(), right = i;
          res = std::max(res, (right - left - 1) * h_now);
        }
        stk.push_back(i);
      }
      return res;
    };
    for (int i = 0; i < m; i++) {
      // 以当前行为底边
      for (int j = 0; j < n; j++) {
        // 更新heights数组
        heights[j] = (matrix[i][j] == '0') ? 0 : (heights[j] + 1);
      }
      ans = std::max(ans, computeArea());
    }
    return ans;
  }
};