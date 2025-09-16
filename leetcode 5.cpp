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
      } else {
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
