constexpr int MOD = 1e9 + 7;

class Solution {
public:
  int lengthAfterTransformations(string s, int t) {
    int n = s.size();
    std::vector f(2, std::vector<int>(26, 0));
    int idx = 0;
    for (char c : s) {
      f[idx][c - 'a']++;
    }
    for (int i = 1; i <= t; i++) {
      idx = i & 1;
      f[idx][0] = f[idx ^ 1][25];
      f[idx][1] = (f[idx ^ 1][0] + f[idx ^ 1][25]) % MOD;
      for (int i = 2; i < 26; i++)
        f[idx][i] = f[idx ^ 1][i - 1];
    }
    int ans = 0;
    for (int i = 0; i < 26; i++)
      ans = (ans + f[idx][i]) % MOD;
    return ans;
  }
};
