#include <algorithm>
#include <cmath>
#include <cstddef>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <memory_resource>
#include <queue>
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

using std::list;
using std::queue;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

class Solution {
public:
  TreeNode *sortedArrayToBST(vector<int> &nums) {
    int n = nums.size();
    return buildTree(nums, 0, n - 1);
  }
  TreeNode *buildTree(vector<int> &nums, int l, int r) {
    if (l > r)
      return nullptr;
    int mid = (l + r) >> 1;
    TreeNode *new_node = new TreeNode(nums[mid]);
    new_node->left = buildTree(nums, l, mid - 1);
    new_node->right = buildTree(nums, mid + 1, r);
    return new_node;
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
  std::vector<int> nums = {9, 9, 8, 8, 7, 6, 5};
  auto ans = std::upper_bound(nums.begin(), nums.end(), 9, std::greater<>());
  std::cout << ans - nums.begin() << std::endl;
  ans = std::lower_bound(nums.begin(), nums.end(), 7, std::greater<>());
  std::cout << ans - nums.begin() << std::endl;
  return 0;
}