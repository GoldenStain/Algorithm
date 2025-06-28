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