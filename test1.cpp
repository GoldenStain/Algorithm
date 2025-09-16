#include <algorithm>
#include <atomic>
#include <cmath>
#include <deque>
#include <iostream>
#include <new>
#include <queue>
#include <stdio.h>
#include <string>
#include <valarray>
#include <vector>

class Solution {
public:
  std::string longestPalindrome(std::string s) {
    std::string t = rebuild(s);
    int center = 0, right_bound = 0;
    int len = t.size();
    std::vector<int> r(len, 0); // 向左/右边延伸的半径长度，不包括自身
    int ans = 0, max_pos = 0;
    for (int i = 1; i < len - 1; i++) {
        int i_mirror = 2 * center - i;
        if (i < right_bound) {
            r[i] = std::min(right_bound - i, r[i_mirror]);
        }
        else {
            r[i] = 0;
        }
        // 有起始字符拦着，不会越界
        while (t[i + r[i] + 1] == t[i - r[i] - 1])
            r[i]++;
        if (i + r[i] > right_bound) {
            right_bound = i + r[i];
            center = i;
        }
        if (r[i] > ans) {
            ans = r[i];
            max_pos = i;
        }
    }
    int start_pos = (max_pos - r[max_pos]) >> 1;
    // 因为r[i]表示延伸半径，不包括自身，所以不用减一
    return s.substr(start_pos, r[max_pos]);
  }
  std::string rebuild(const std::string &s) {
    if (s.size() == 0)  
        return "^$";
    std::string res = "^";
    for (int i = 0; i < s.size(); i++) {
        res.append(1, '#');
        res.append(1, s[i]);
    }
    res.append(1, '#');
    res.append(1, '$');
    return res;
  }
};

template <typename T> class MySharedPtr {
private:
  T *my_ptr = nullptr;
  std::atomic<size_t> *my_ref_count = nullptr;

public:
};

struct TreeNode {
  int val;
  TreeNode *left = nullptr, *right = nullptr;
  TreeNode(int v) : val(v) {}
};

namespace test {
class Solution {
public:
  std::vector<std::vector<int>> Zloop(TreeNode *root) {
    if (root == nullptr) {
      return std::vector<std::vector<int>>{};
    }
    std::vector<std::vector<int>> ans;
    std::queue<TreeNode *> q;
    q.push(root);
    ans.push_back(std::vector<int>{root->val});
    bool flag = true; // false right->left, true left->right
    while (q.size()) {
      flag = !flag;
      std::deque<int> tmp_q;
      int size = q.size();
      while (size--) {
        auto top = q.front();
        q.pop();
        std::cout << "DEBUG: " << top->val << std::endl;
        if (top->left) {
          q.push(top->left);
          if (flag) {
            tmp_q.push_back(top->left->val);
          } else
            tmp_q.push_front(top->left->val);
        }
        if (top->right) {
          q.push(top->right);
          if (flag) {
            tmp_q.push_back(top->right->val);
          } else
            tmp_q.push_front(top->right->val);
        }
      }
      // over
      std::vector<int> now_ans(tmp_q.begin(), tmp_q.end());
      ans.push_back(now_ans);
    }
    return ans;
  }
};
} // namespace test

int main() {
  test::Solution s;
  TreeNode *root = new TreeNode(1), *a = new TreeNode(2), *b = new TreeNode(3),
           *c = new TreeNode(4), *d = new TreeNode(5), *e = new TreeNode(6);
  root->left = a;
  root->right = b;
  a->left = c;
  a->right = d;
  b->right = e;
  auto &ans = s.Zloop(root);
  for (auto vi : ans) {
    for (auto vii : vi)
      std::cout << vii << " ";
    std::cout << std::endl;
  }
  return 0;
}
