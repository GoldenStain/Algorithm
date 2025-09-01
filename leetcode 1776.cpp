class Solution {
public:
  vector<double> getCollisionTimes(vector<vector<int>> &cars) {
    int n = cars.size();
    std::vector<int> stk;
    std::vector<double> ans(n, -1);
    for (int i = n - 1; ~i; i--) {
      int pi = cars[i][0], vi = cars[i][1];
      while (stk.size()) {
        if (cars[stk.back()][1] >= vi) {
          stk.pop_back();
          continue;
        }
        if (stk.empty())
          break;
        // 当前车能追上栈顶的车了
        double T =
            (cars[stk.back()][0] - pi) * 1.0 / (vi - cars[stk.back()][1]);
        if (ans[stk.back()] > 0 && T > ans[stk.back()]) {
          stk.pop_back();
          continue; // 栈顶的车在被追上之前追上了更前面的车，因此需要用更前面的车为基准来计算追击问题
        }
        ans[i] = T;
        break;
      }
      stk.push_back(i);
    }
    return ans;
  }
};