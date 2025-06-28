// Normal solution
class Solution {
public:
  bool isSubsequence(string s, string t) {
    int lens = s.size(), lent = t.size(), cur = 0;
    for (int i = 0; i < lent; i++) {
      if (t[i] == s[cur])
        cur++;
    }
    return (cur == lens);
  }
};

// Advanced solution
// 定义第一维为n+1的好处：
// 1. 预处理的时候不用特判（否则需要特判i < n-1)
// 2. 输入的t可能是空串，如果第一维开n，那么直接就内存访问越界了
class Solution {
public:
  bool isSubsequence(string s, string t) {
    int n = t.size();
    // nxt[i][c]表示大于等于i的下标位置当中，最近的一个字符c的位置。
    std::vector nxt(n + 1, std::array<int, 26>{});
    std::fill(nxt[n].begin(), nxt[n].end(), n);
    // 预处理
    for (int i = n - 1; i >= 0; i--) {
      int idx = t[i] - 'a';
      nxt[i] = nxt[i + 1];
      nxt[i][idx] = i;
    }
    int cur = -1;
    for (int i = 0; i < s.size(); i++) {
      int idx = s[i] - 'a';
      cur = nxt[cur + 1][idx];
      if (cur == n)
        return false;
    }
    return true;
  }
};