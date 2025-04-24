class Solution {
public:
  int longestPalindrome(string s) {
    std::unordered_map<char, int> M;
    for (auto &ci : s) {
      M[ci]++;
    }
    int ans = 0;
    for (auto &pi : M) {
      ans += (pi.second >> 1) << 1; // 偶数个两个都能用上，奇数个有一个会落单
      if (ans % 2 == 0 && (pi.second & 1))
        ans++; // 这种条件下，落单的能用上
    }
    return ans;
  }
};
