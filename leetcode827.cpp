#include <algorithm>
#include <array>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstddef>
#include <deque>
#include <features.h>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <istream>
#include <iterator>
#include <list>
#include <memory>
#include <memory_resource>
#include <numeric>
#include <queue>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define For(i, j, n) for (int i = j; i <= n; ++i)
#ifdef DEBUG
#define DEBUG_LOG(fmt, ...)                                                    \
  do {                                                                         \
    fprintf(stderr, fmt, ##__VA_ARGS__);                                       \
  } while (0);
#else
#define DEBUG_LOG(fmt, ...)                                                    \
  do {                                                                         \
  } while (0);
#endif

template <typename T> inline T read() {
  T x = 0;
  int f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

using std::queue;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

namespace leetcode {
class Solution {
  int dx[4] = {-1, 1, 0, 0};
  int dy[4] = {0, 0, -1, 1};

public:
  int largestIsland(vector<vector<int>> &grid) {
    // 不需要vis数组，可以利用grid本身充当vis数组
    int n = grid.size();
    vector<int> area;
    auto dfs = [&](this auto &&dfs, int x, int y) -> int {
      grid[x][y] = area.size() + 2;
      int size = 1;
      for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n || grid[nx][ny] != 1)
          continue;
        size += dfs(nx, ny);
      }
      return size;
    };
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        if (grid[i][j] != 1)
          continue;
        area.push_back(dfs(i, j));
      }
    // 特判
    if (area.empty()) {
      return 1;
    }
    int ans = 0;
    std::unordered_set<int> S;
    // 统计修改后的面积
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        if (grid[i][j])
          continue;
        S.clear();
        // 这个格子改为1，本身有一格面积。
        int a = 1;
        for (int k = 0; k < 4; k++) {
          int x = i + dx[k], y = j + dy[k];
          if (x < 0 || x >= n || y < 0 || y >= n || !grid[x][y] ||
              !(S.insert(grid[x][y]).second))
            continue;
          a += area[grid[x][y] - 2];
        }
        ans = std::max(ans, a);
      }
    // 如果所有格子都是1，那么ans就不会被改动，ans始终是0
    return ans ? ans : n * n;
  }
};
}; // namespace leetcode

int main() {
  leetcode::Solution sol = leetcode::Solution();
  vector<vector<int>> matrix = {{0, 0}, {0, 1}};
  std::cout << sol.largestIsland(matrix);
  return 0;
}