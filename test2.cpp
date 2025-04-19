#include <algorithm>
#include <cmath>
#include <cstddef>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
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
  long long countFairPairs(vector<int> &nums, int lower, int upper) {
    std::sort(nums.begin(), nums.end());
    int n = nums.size();
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int B = upper - nums[i], A = lower - nums[i];
        std::vector<int>::iterator right_bound = std::upper_bound(nums.begin(), nums.begin() + i, B),
        left_bound = std::lower_bound(nums.begin(), nums.begin() + i, A);
        // 同样地，要避免重复
        ans += (long long)(right_bound - left_bound);
    }
    return ans;
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() { return 0; }