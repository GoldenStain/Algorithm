#include <algorithm>
#include <atomic>
#include <climits>
#include <cmath>
#include <deque>
#include <iostream>
#include <new>
#include <queue>
#include <stdio.h>
#include <string>
#include <valarray>
#include <vector>

template <typename T> using vector = std::vector<T>;

template <typename T> class MySharedPtr {
private:
  T *my_ptr = nullptr;
  std::atomic<size_t> *my_ref_count = nullptr;

public:
};

struct TreeNode {
  int val;
  TreeNode *left = nullptr, *right = nullptr;
  TreeNode(int v) : val(v) {}
};

class Solution {
public:
  bool find132pattern(vector<int> &nums) {
    int n = nums.size();
    vector prefix_min(
        n + 1,
        INT_MAX); // prefix_min[i]表示0~i-1的最小值，之所以表示0~i的最小值是因为如果对下标减一的话，需要对0这样的位置做特判
    std::vector<int> stk;
    for (int i = 0; i < n; i++) {
      while (stk.size() && nums[stk.back()] <= nums[i]) {
        stk.pop_back();
      }
      if (stk.size() && prefix_min[stk.back()] < nums[i])
        return true;
      stk.push_back(i);
      // 更新的时候对下标进行偏移
      // 正常的前缀最小值：prefix_min[i] = std::min(prefix_min[i - 1], nums[i])
      // 这里因为是表示0~i-1的最小值，所以要做偏移
      prefix_min[i + 1] = std::min(prefix_min[i], nums[i]);
    }
    return false;
  }
};

int main() {
  test::Solution s;
  TreeNode *root = new TreeNode(1), *a = new TreeNode(2), *b = new TreeNode(3),
           *c = new TreeNode(4), *d = new TreeNode(5), *e = new TreeNode(6);
  root->left = a;
  root->right = b;
  a->left = c;
  a->right = d;
  b->right = e;
  auto &ans = s.Zloop(root);
  for (auto vi : ans) {
    for (auto vii : vi)
      std::cout << vii << " ";
    std::cout << std::endl;
  }
  return 0;
}
