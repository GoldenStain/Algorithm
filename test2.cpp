#include <algorithm>
#include <climits>
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

using std::queue;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

class Solution {
private:
  struct Cmp {
    bool operator()(ListNode *a, ListNode *b) { return a->val > b->val; }
  };

public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    std::priority_queue<ListNode *, std::vector<ListNode *>, Cmp> Q;
    ListNode *dummy = new ListNode();
    for (auto &li : lists) {
      // 小心空节点，如果不小心把nullptr放进堆里，就会导致我们的Cmp报错（因为空节点没有val）
      if (li)
        Q.push(li);
    }
    ListNode *st = dummy;
    while (Q.size()) {
      auto tmp = Q.top();
      st->next = tmp;
      Q.pop();
      // 小心空节点
      if (tmp->next)
        Q.push(tmp->next);
      st = st->next;
    }
    st->next = nullptr;
    return dummy->next;
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