// DP
class Solution {
public:
  int longestValidParentheses(string s) {
    int n = s.size();
    std::vector<int> f(n, 0);
    int ans = 0;
    for (int i = 1; i < n; i++) {
      if (s[i] == '(')
        continue;
      if (s[i - 1] == '(')
        // 这里要注意三目运算符的优先级问题
        f[i] = ((i - 2) >= 0 ? f[i - 2] : 0) + 2;
      else if (i - 1 - f[i - 1] >= 0 && s[i - 1 - f[i - 1]] == '(')
        f[i] = f[i - 1] + 2 + (i - 2 - f[i - 1] >= 0 ? f[i - 2 - f[i - 1]] : 0);
      ans = std::max(ans, f[i]);
    }
    return ans;
  }
};

// 双指针写法
class Solution {
public:
  int longestValidParentheses(string s) {
    int left = 0, right = 0;
    int n = s.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (s[i] == '(')
        left++;
      else
        right++;
      if (left == right)
        ans = std::max(ans, left * 2);
      else if (right > left)
        left = 0, right = 0;
    }
    left = 0;
    right = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (s[i] == '(')
        left++;
      else
        right++;
      if (left == right)
        ans = std::max(ans, left * 2);
      else if (left > right)
        left = 0, right = 0;
    }
    return ans;
  }
};

// 栈写法
class Solution {
public:
  int longestValidParentheses(string s) {
    std::vector<int> stk;
    stk.push_back(-1);
    int ans = 0;
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == '(') {
        stk.push_back(i);
      } else {
        stk.pop_back();
        if (stk.empty()) {
          // 如果此时栈为空，说明刚才出栈的其实是“上一个多余右括号”的下标
          // 而当前的也是右括号，说明“上一个多余右括号”该变成当前这个了
          stk.push_back(i);
        } else {
          // 栈不空：
          // 1. 栈顶是左括号
          // 2. 栈顶是“上一个多余右括号”
          // 这两种情况都可以这么计算
          ans = std::max(ans, i - stk.back());
        }
      }
    }
    return ans;
  }
};