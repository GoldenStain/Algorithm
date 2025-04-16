#include <cstddef>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
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
using std::vector;

class Solution {
public:
  int findKthLargest(vector<int> &nums, int k) {
    int n = nums.size();
    return worker(nums, 0, n - 1, k - 1);
  }
  int worker(vector<int> &nums, int l, int r, int k) {
    if (l == r)
      return nums[k];
    int pivot = (l + r + 1) >> 1;
    pivot = nums[pivot];
    int i = l - 1, j = r + 1;
    while (i < j) {
      do {
        i++;
      } while (nums[i] > pivot);
      do {
        j--;
      } while (nums[j] < pivot);
      if (i < j)
        std::swap(nums[j], nums[i]);
    }
    if (i > k)
      return worker(nums, l, i, k);
    else
      return worker(nums, i, r, k);
  }
};

int main() {
  vector<int> nums = {3,2,1,5,6,4};
  Solution s;
  std::cout << s.findKthLargest(nums, 2) << std::endl;
  return 0;
}