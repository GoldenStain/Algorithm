constexpr long long MOD = 1e9 + 7;
class Solution {
public:
  int countGoodArrays(int n, int m, int k) {
    std::vector<long long> jc(n + 1, 1);
    [&]() {
      for (int i = 2; i <= n; i++)
        jc[i] = ((jc[i - 1]) * i) % MOD;
    }();
    auto quick_pow = [&](int n, int k) -> long long {
      long long res = 1, base = n;
      while (k) {
        if (k & 1)
          res = res * base % MOD;
        // 注意要先更新res再更新base
        base = base * base % MOD;
        k >>= 1;
      }
      return res;
    };
    auto rev = [&](long long k) -> long long {
      long long res = 1;
      int cnt = MOD - 2;
      while (cnt) {
        if (cnt & 1)
          res = res * k % MOD;
        k = k * k % MOD;
        cnt >>= 1;
      }
      return res;
    };
    auto combination = [&](int n, int m) -> long long {
      long long res = jc[n] * rev(jc[m]) % MOD * rev(jc[n - m]) % MOD;
      return res;
    };
    long long ans =
        combination(n - 1, k) * m % MOD * quick_pow(m - 1, n - k - 1) % MOD;
    return ans;
  }
};