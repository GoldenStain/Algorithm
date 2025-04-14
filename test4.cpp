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
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    quickSort(dummy, head, nullptr);
    return dummy->next;
  }

private:
  void quickSort(ListNode *dummy, ListNode *head, ListNode *tail) {
    if (head == tail)
      return;
    ListNode *p = head, *q = p->next;
    ListNode *prev_p = dummy, *prev_q = p;
    while (q != tail) {
      if (q->val < head->val) {
        prev_p = p;
        p = p->next;
        if (p != q) {
          swapNode(prev_p, prev_q);
          // swapNode执行之后，修改了链表结构，p跑到后面去了，q则在前面，我们需要再交换一下指针的指向
          std::swap(p, q);
        }
      }
      prev_q = q;
      q = q->next;
    }
    if (p != head) {
      swapNode(dummy, prev_p);
      std::swap(p, head);
    }

    // 因为我们改变了链表结构，所以head可能不再是head了，我们要用dummy->next来定位链表头
    quickSort(dummy, dummy->next, p);
    quickSort(p, p->next, tail);
  }

  void swapNode(ListNode *prev_p, ListNode *prev_q) {
    ListNode* p = prev_p->next, *q = prev_q->next;
    ListNode* new_p = new ListNode(q->val), *new_q = new ListNode(p->val);
    new_p->next = p->next;
    new_q->next = q->next;
    prev_p->next = new_p;
    prev_q->next = new_q;
  }
};

int main() {
  Solution s;
  ListNode *arr = new ListNode[5];
  arr[0].val = 4;
  arr[1].val = 1;
  arr[2].val = -4;
  arr[3].val = 2;
  arr[4].val = -1;
  for (int i = 0; i < 4; i++)
    arr[i].next = &arr[i + 1];
  s.quickSortList(arr);
  ListNode *st = arr;
  while (st) {
    std::cout << st->val << " ";
    st = st->next;
  }
  return 0;
}
