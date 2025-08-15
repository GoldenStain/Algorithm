#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <stack>
#include <vector>

namespace leetcode {
template <typename T> using vector = std::vector<T>;
template <typename T> using function = std::function<T>;
class Solution {
public:
  vector<int> searchRange(vector<int> &nums, int target) {
    vector<int> ans;
    nums.push_back(INT_MAX);
    int n = nums.size();
    function<int()> find_lower = [&]() -> int {
      int l = 0, r = n - 1;
      while (l < r) {
        int mid = (l + r) >> 1;
        if (nums[mid] >= target) {
          r = mid;
        } else {
          l = mid + 1;
        }
      }
      return l;
    };
    function<int()> find_upper = [&]() -> int {
      int l = 0, r = n - 1;
      while (l < r) {
        int mid = (l + r) >> 1;
        if (nums[mid] > target) {
          r = mid;
        } else {
          l = mid + 1;
        }
      }
      return l;
    };
    int lower_pos = find_lower();
    if (lower_pos == n || nums[lower_pos] != target) {
      ans = {-1, -1};
    } else {
      int upper_pos = find_upper();
      ans = {lower_pos, upper_pos - 1};
    }
    return ans;
  }
};
}; // namespace leetcode

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

int main() {
  int x = 20000;
  std::cout << std::log2(x) << std::endl;
}