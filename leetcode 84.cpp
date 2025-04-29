using std::cin, std::cout;
using std::vector;
class Solution {
public:
  int largestRectangleArea(vector<int> &heights) {
    vector<int> stk;
    int ans = 0, n = heights.size();
    vector<int> left(n, -1), right(n, n); // -1和n对应边界情况
    for (int i = 0; i < n; i++) {
      while (stk.size() && heights[i] < heights[stk.back()]) {
        right[stk.back()] = i;
        stk.pop_back();
      }
      if (stk.size())
        left[i] = stk.back();
      stk.push_back(i);
    }
    for (int i = 0; i < n; i++)
      ans = std::max(ans, (right[i] - left[i] - 1) * heights[i]);
    return ans;
  }
};

// 写法二
class Solution {
public:
  int largestRectangleArea(vector<int> &heights) {
    std::vector<int> stk;
    int n = heights.size();
    std::vector<int> left_(n, -1),
        right_(
            n,
            n); // 初始化一个非法值，因为我们最后计算答案的时候，是不包括left和right的
    // 详见计算公式
    for (int i = 0; i < n; i++) {
      while (stk.size() && heights[stk.back()] >= heights[i]) {
        right_[stk.back()] = i;
        stk.pop_back();
      }
      if (stk.size())
        left_[i] = stk.back();
      stk.push_back(i);
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
      ans = std::max(ans, (right_[i] - left_[i] - 1) * heights[i]);
    return ans;
  }
};