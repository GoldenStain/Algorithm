#include <algorithm>
#include <atomic>
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
                dp[i][j] = std::min(dp[i][j], dp[break_point][j - 1] + cost[break_point + 1][i]);
            }
        }
    }
    return dp[n - 1][k];
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
