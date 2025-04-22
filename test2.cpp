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
public:
  ListNode *sortList(ListNode *head) {
    if (!head || !head->next)
      return head;
    return mergeSort(head, nullptr);
  }

private:
  // [head, tail) 左闭右开区间
  ListNode *mergeSort(ListNode *head, ListNode *tail) {
    if (head == tail)
      return nullptr;
    // 只有一个节点的话，我们手动把这个部分摘出来变成一个单独的链表
    // 因为合并链表算法要求输入的链表结尾都是nullptr
    // 这个操作在经过递归合并之后，可以保证参与操作的所有链表，其结尾都是nullptr
    if (head->next == tail) {
      head->next = nullptr;
      return head;
    }
    ListNode *mid = findMid(head, tail); // 后半部分第一个点
    return merge(mergeSort(head, mid), mergeSort(mid, tail));
  }
  inline ListNode *findMid(ListNode *head, ListNode *tail) {
    ListNode *slow = head, *fast = head;
    while (fast != tail && fast->next != tail) {
      fast = fast->next->next;
      slow = slow->next;
    }
    return slow;
  }
  ListNode *merge(ListNode *a, ListNode *b) {
    ListNode *dummy = new ListNode(-1), *st = dummy;
    while (a && b) {
      if (a->val <= b->val) {
        st->next = a;
        a = a->next;
      } else {
        st->next = b;
        b = b->next;
      }
      st = st->next;
    }
    if (a)
      st->next = a;
    if (b)
      st->next = b;
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