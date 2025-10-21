using PII = std::pair<int, int>;
using string = std::string;
class Solution {
public:
  string findLexSmallestString(string s, int a, int b) {
    int n = s.length();
    // step = k * gcd(n, b)
    string ans;
    int step = std::gcd(n, b);
    int g = std::gcd(10, a);
    auto modify = [&](string &tmp, int idx) -> void {
      int num = tmp[idx] - '0';
      int changed = (num % g - num) + 10;
      if (changed) {
        for (int i = idx; i < n; i += 2) {
          tmp[i] = (tmp[i] - '0' + changed) % 10 + '0';
        }
      }
    };
    for (int i = 0; i < n; i += step) {
      string tmp = s.substr(i) + s.substr(0, i);
      modify(tmp, 1);
      if (step & 1)
        modify(tmp, 0);
      if (ans.empty() || ans > tmp)
        ans = tmp;
    }
    return ans;
  }
};