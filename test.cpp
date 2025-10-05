#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

template <typename T> using vector = std::vector<T>;
namespace leetcode {
using PII = std::pair<int, int>;
class Solution {
public:
  int swimInWater(vector<vector<int>> &grid) {
    int n = grid.size();
    vector<PII> index(n * n);
    fa.resize(n*n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        index[grid[i][j]] = {i, j};
        fa[i * n + j] = i * n + j;
      }
    vector<PII> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int thre = 0; thre < n * n; thre++) {
      auto [x, y] = index[thre];
      for (auto &[dx, dy] : directions) {
        int i = x + dx, j = y + dy;
        if (i < 0 || i >= n || j < 0 || j >= n || grid[i][j] > thre)
          continue;
        int pa = find(x * n + y), pb = find(i * n + j);
        merge(pa, pb);
      }
      if (find(0) == find(n * n - 1))
        return thre;
    }
    return n * n - 1;
  }

private:
  vector<int> fa;
  void merge(int a, int b) { fa[b] = a; }
  int find(int x) {
    if (x == fa[x])
      return x;
    return fa[x] = find(fa[x]);
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