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

// best solution
class Solution {
public:
  int largestRectangleArea(vector<int> &heights) {
    heights.insert(heights.begin(), 0);
    heights.push_back(
        0); // 放两个padding的值，等价于原先Solution当中，把left和right数组初始化为非法值
    // 如果while条件里加上等号，那么insert那里就要改成-1
    // 如果while条件里改成等号，insert也保持0，那么循环内部计算答案的时候就需要加一个if语句判定栈是否为空
    std::vector<int> stk;
    int n = heights.size(), ans = 0;
    for (int i = 0; i < n; i++) {
      while (!stk.empty() && heights[stk.back()] > heights[i]) {
        int now_height = heights[stk.back()];
        stk.pop_back();
        // 此时的栈顶是：now_height左边第一个比它小的
        // 不用担心进行一次出栈操作后，栈上就为空了，
        // 因为我们进行了padding操作，这里是一定有0来垫底的
        int _left = stk.back() + 1, _right = i - 1;
        // 两个比now_height更小的柱子中间，所夹住的部分，就是now_height所构成的合法矩形
        ans = std::max(ans, (_right - _left + 1) * now_height);
      }
      stk.push_back(i);
    }
    return ans;
  }
};
