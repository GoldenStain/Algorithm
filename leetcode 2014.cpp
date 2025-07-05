class Solution {
public:
  string longestSubsequenceRepeatedK(string s, int k) {
    int cnt[26]{};
    for (char &c : s) {
      cnt[c - 'a']++;
    }
    std::string str;
    for (int i = 25; i >= 0; i--) {
      str.insert(str.end(), cnt[i] / k, i + 'a');
    }
    std::string ans;
    permutation(str, [&](std::string temp) -> bool {
      bool is_sub = Solution::isSubsequence(temp, s, k);
      if (!is_sub)
        return false;
      if (temp.size() > ans.size())
        ans = temp;
      return true;
    });
    return ans;
  }
  static bool isSubsequence(std::string t, std::string s, int k) {
    int cur = 0, len = t.size();
    for (auto &c : s) {
      if (c == t[cur % len]) {
        cur++;
        // if (cur == len * k)
        //   return true;
      }
    }
    // 注意这里有一个细节，我们要么就在每个循环内部判定是否要return
    // 要么就在这里判定cur是否超过目标长度
    // 不能是等于，等于会导致误判
    // 例如输入s="bbabbabbbbabaababab"
    // 答案是"bbbb"
    // 但是想要搜到"bbbb"我们得先搜到"bb"，然后是"bbb"...最后是"bbbb"
    // 但是对于"bb"来说,cur最后是12,而len*k=2*3=6，如果判定严格等于的话，就会导致错误剪枝，丢失答案
    return cur >= len * k;
  }
  // str:输入的，用于全排列的字符串
  // f:用来进行判定的函数
  template <typename T> void permutation(const std::string &str, T &&f) {
    int n = str.size();
    std::string path;
    path.reserve(n);
    std::vector<char> vis(n, false);
    auto dfs = [&](this auto &&dfs) -> void {
      if (!path.empty() && !f(path)) {
        return;
      }
      if (path.size() == n) {
        return;
      }
      for (int i = 0; i < n; i++) {
        if (vis[i] || (i && str[i] == str[i - 1] && !vis[i - 1]))
          continue;
        vis[i] = true;
        path += str[i];
        dfs();
        vis[i] = false;
        path.pop_back();
      }
    };
    dfs();
  }
};

// super solution
class Solution {
public:
  string longestSubsequenceRepeatedK(string s, int k) {
    int cnt[26]{};
    int s_len = s.size();
    for (char &c : s) {
      cnt[c - 'a']++;
    }
    std::string str;
    std::vector<std::array<int, 26>> nxt(s_len + 1);
    std::fill(nxt[s_len].begin(), nxt[s_len].end(), s_len);
    for (int i = s_len - 1; i >= 0; i--) {
      nxt[i] = nxt[i + 1];
      nxt[i][s[i] - 'a'] = i;
    }
    for (int i = 25; i >= 0; i--) {
      str.insert(str.end(), cnt[i] / k, i + 'a');
    }
    std::string ans;
    permutation(str, [&](std::string temp) -> bool {
      bool is_sub = Solution::isSubsequence(nxt, temp, s, k);
      if (!is_sub)
        return false;
      if (temp.size() > ans.size())
        ans = temp;
      return true;
    });
    return ans;
  }
  static bool isSubsequence(const std::vector<std::array<int, 26>> &nxt,
                            std::string t, std::string s, int k) {
    int n = s.size(), cur = -1;
    while (k--) {
      for (char &c : t) {
        cur = nxt[cur + 1][c - 'a'];
        if (cur == n)
          return false;
      }
    }
    return true;
  }
  // str:输入的，用于全排列的字符串
  // f:用来进行判定的函数
  template <typename T> void permutation(const std::string &str, T &&f) {
    int n = str.size();
    std::string path;
    path.reserve(n);
    std::vector<char> vis(n, false);
    auto dfs = [&](this auto &&dfs) -> void {
      if (!path.empty() && !f(path)) {
        return;
      }
      if (path.size() == n) {
        return;
      }
      for (int i = 0; i < n; i++) {
        if (vis[i] || (i && str[i] == str[i - 1] && !vis[i - 1]))
          continue;
        vis[i] = true;
        path += str[i];
        dfs();
        vis[i] = false;
        path.pop_back();
      }
    };
    dfs();
  }
};