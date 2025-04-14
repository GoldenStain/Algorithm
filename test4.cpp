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
  ListNode *quickSortList(ListNode *head) {
    if (!head || !head->next)
      return head;
    quickSort(head, nullptr);
    return head;
  }
  // 对[head, tail)区间进行排序
  void quickSort(ListNode *head, ListNode *tail) {
    if (head == tail)
      return;
    ListNode *p = head, *q = p->next;
    // (head, p]都是小于head->val的，(p, q]都是大于等于的
    while (q != tail) {
      if (q->val < head->val) {
        p = p->next;
        std::swap(p->val, q->val);
      }
      q = q->next;
    }
    // 如果head和p不在同一个点，把head的值放到p上，即把哨兵放到p，那么,[head,
    // p)<pivot, (p, tail)>=pivot，下次排序就不用考虑p，区间就缩小了
    if (head != p)
      std::swap(head->val, p->val);
    quickSort(head, p);
    quickSort(p->next, tail);
  }
};

int main() {
  int x = 0x3f3f3f3f;
  std::cout << x << std::endl;
  return 0;
}
