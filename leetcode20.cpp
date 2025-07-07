#include <iostream>
#include <stack>

class Solution {
  using string = std::string;
  typedef std::pair<char, int> PCI;

public:
  bool isValid(string s) {
    for (int i = 0; i < s.length(); i++) {
      char c = s[i];
      if (c == '(')
        s1.push({c, i});
      else if (c == '[')
        s2.push({c, i});
      else if (c == '{')
        s3.push({c, i});
      else if (c == ')') {
        if (s1.empty())
          return false;
        int idx = s1.top().second;
        if (check_stack(s2, idx) || check_stack(s3, idx))
          return false;
        s1.pop();
      } else if (c == ']') {
        if (s2.empty())
          return false;
        int idx = s2.top().second;
        if (check_stack(s1, idx) || check_stack(s3, idx))
          return false;
        s2.pop();
      } else {
        if (s3.empty())
          return false;
        int idx = s3.top().second;
        if (check_stack(s1, idx) || check_stack(s2, idx))
          return false;
        s3.pop();
      }
    }
    return s1.empty() && s2.empty() && s3.empty();
  }

private:
  std::stack<PCI> s1, s2, s3;
  bool check_stack(std::stack<PCI> &s, int idx) {
    if (s.empty())
      return false;
    int s_idx = s.top().second;
    return s_idx > idx;
  }
};