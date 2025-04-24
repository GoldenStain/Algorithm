class Solution {
public:
  string minWindow(string s, string t) {
    std::unordered_map<char, int> M;
    std::unordered_set<char> S, MS;
    std::string ans = "";
    int ans_len = 1e6;
    for (int i = 0; i < t.size(); i++) {
      S.insert(t[i]);
      M[t[i]]--;
    }
    int hh = 0, tt = 0;
    for (; tt < s.size(); tt++) {
      if (S.count(s[tt])) {
        M[s[tt]]++;
        if (M[s[tt]] >= 0)
          MS.insert(s[tt]);
      }
      if (MS.size() == S.size()) {
        // update
        while (hh <= tt && (!S.count(s[hh]) || M[s[hh]] > 0)) {
          if (S.count(s[hh]))
            M[s[hh]]--;
          hh++;
        }
        // check
        int len = tt - hh + 1;
        if (ans_len > len) {
          ans_len = len;
          ans = s.substr(hh, len);
        }
      }
    }
    return ans;
  }
};