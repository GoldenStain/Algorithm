using string = std::string;
class Solution {
  std::unordered_map<char, char> Ms, Mt;

public:
  bool isIsomorphic(string s, string t) {
    int ls = s.size(), lt = t.size();
    if (ls != lt) {
      return false;
    }
    for (int i = 0; i < ls; i++) {
      char cs = s[i], ct = t[i];
      if ((Ms.contains(cs) && Ms[cs] != ct) ||
          (Mt.contains(ct) && Mt[ct] != cs))
        return false;
      Ms[cs] = ct;
      Mt[ct] = cs;
    }
    return true;
  }
};