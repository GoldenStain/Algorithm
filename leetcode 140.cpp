class Solution {
  std::unordered_set<std::string> S;
  vector<bool> vis;

public:
  vector<string> wordBreak(string s, vector<string> &wordDict) {
    S = std::unordered_set<std::string>(wordDict.begin(), wordDict.end());
    std::vector<std::vector<string>> splited_words(s.size() + 1,
                                                   vector<string>{});
    vis = std::vector<bool>(s.size() + 1, false);
    dfs(0, splited_words, s);
    return splited_words[0];
  }
  void dfs(int pos, std::vector<std::vector<string>> &splited_words,
           string &s) {
    if (vis[pos])
      return;
    vis[pos] = true;
    if (pos == s.size()) {
      // 需要手动放一个空的字符串，否则不能跟前面的接上
      splited_words[pos] = {""};
      return;
    }
    for (int i = pos + 1; i <= s.size(); i++) {
      // pos ~ i-1 是当前的，i~往后是后面一串的
      string tmp = s.substr(pos, i - pos);
      dfs(i, splited_words, s);
      if (S.count(tmp)) {
        for (auto &si : splited_words[i]) {
          splited_words[pos].emplace_back(si.empty() ? tmp : tmp + " " + si);
        }
      }
    }
  }
};