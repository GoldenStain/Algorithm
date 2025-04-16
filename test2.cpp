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

class LRUCache {
  using PII = std::pair<int, int>;

public:
  LRUCache(int capacity) : capacity_(capacity) {}

  int get(int key) {
    auto kv_pair = M.find(key);
    if (kv_pair == M.end()) {
      return -1;
    }
    auto link_node = kv_pair->second;
    int ans = link_node->second;
    replace_node(link_node, ans);
    M[key] = link_.begin();
    return ans;
  }

  void put(int key, int value) {
    auto kv_pair = M.find(key);
    if (kv_pair == M.end()) {
      link_.push_front({key, value});
      M[key] = link_.begin();
      if (size_ == capacity_)
        remove_old();
      else
       size_++;
    } else {
      replace_node(kv_pair->second, value);
      M[key] = link_.begin();
    }
  }

private:
  int capacity_ = 0, size_ = 0;
  unordered_map<int, list<PII>::iterator> M;
  list<PII> link_;
  void replace_node(list<PII>::iterator node, int value) {
    int key = node->first;
    link_.erase(node);
    link_.push_front({key, value});
  }
  void remove_old() {
    auto node = link_.back();
    int key = node.first;
    link_.pop_back();
    M.erase(key);
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() { return 0; }