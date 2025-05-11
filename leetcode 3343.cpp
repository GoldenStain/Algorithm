constexpr int N = 41;
constexpr int MOD = 1'000'000'007;

// 这里命名成pow会和标准库冲突，导致不确定调用哪个，所以最好写成一个标准库不存在的名字
long long quick_pow(long long x, int n) {
  long long res = 1ll;
  for (; n; n /= 2) {
    if (n & 1) {
      res = res * x % MOD;
    }
    x = x * x % MOD;
  }
  return res;
}

long long fac[N], inverse_fac[N];

// 语义更清晰，一眼就知道这部分是在执行初始化工作，还不需要显式地进行调用
auto init = [] {
  fac[0] = 1ll;
  for (int i = 1; i < N; i++)
    fac[i] = fac[i - 1] * i % MOD;
  inverse_fac[N - 1] = quick_pow(fac[N - 1], MOD - 2);
  // 不需要针对每个i，都调用快速幂计算逆元，那样子太慢了
  // 只需要用快速幂得到最后一个逆元，前面的部分都能够递推计算
  for (int i = N - 1; i; i--) {
    inverse_fac[i - 1] = inverse_fac[i] * i % MOD;
  }
  return 0;
}();

class Solution {
public:
  int countBalancedPermutations(string num) {
    int cnt[10]{0}, total = 0;
    for (char ci : num) {
      cnt[ci - '0']++;
      total += ci - '0';
    }
    if (total & 1)
      return 0;
    // 利用库函数计算前缀和
    std::partial_sum(cnt, cnt + 10, cnt);
    int n = num.size(), n1 = n >> 1;
    // 自动推导模板参数类型，从C++11引入
    vector memo(10,
                vector(n1 + 1, vector<int>(total / 2 + 1, -1))); // -1表示未计算
    // C++引入的“显式模板参数传递的递归lambda
    // left1表示当前多重集还需要分配几个数字，left2表示另外一个多重集
    // 这里需要显式写出->int，否则会因为我们的返回值既有bool又有int而推导出矛盾
    auto dfs = [&](this auto &dfs, int i, int left1, int left_sum) -> int {
      if (i < 0) {
        return left_sum == 0;
      }
      int &res = memo[i][left1][left_sum];
      if (~res) {
        return res;
      }
      res = 0;
      int left2 = cnt[i] - left1, cur_num = cnt[i] - (i ? cnt[i - 1] : 0);
      // 因为要保证left1和left2都合法，所以k的上下界都有约束
      // 显然有：k <= left1；同时需要满足：cnt[i] - k <=
      // left2，即对面多重集的k也不能超过它们剩下的数字总个数
      for (int k = std::max(0, cur_num - left2);
           k <= std::min(cur_num, left1) && k * i <= left_sum; k++) {
        int r = dfs(i - 1, left1 - k, left_sum - k * i);
        res = (res + r * inverse_fac[k] % MOD * inverse_fac[cur_num - k]) % MOD;
      }
      return res;
    };
    // 注意我们求的是一个多重集，所以个数和总和用的都是真正总数目的一半
    return dfs(9, n1, total >> 1) * fac[n1] % MOD * fac[n - n1] % MOD;
  }
};

// DP solution
class Solution {
public:
  int countBalancedPermutations(string num) {
    int cnt[10]{};
    int total = 0;
    for (char c : num) {
      cnt[c - '0']++;
      total += c - '0';
    }

    if (total % 2) {
      return 0;
    }

    int n = num.size();
    int n1 = n / 2;
    vector f(n1 + 1, vector<int>(total / 2 + 1));
    f[0][0] = 1;
    int sc = 0, s = 0;
    for (int i = 0; i < 10; i++) {
      int c = cnt[i];
      // sc是总个数，s是总和
      sc += c;
      s += c * i;
      // 保证 left2 <= n-n1，即 left1 >= sc-(n-n1)
      // 只要最外层是倒序循环，就能保证我们每次使用的都是上一轮的值，内部正序倒序均可，只要满足物理意义即可.
      for (int left1 = min(sc, n1); left1 >= max(sc - (n - n1), 0); left1--) {
        int left2 = sc - left1;
        // 保证分给第二个集合的元素和 <= total/2，即 leftS >= s-total/2
        for (int left_s = min(s, total / 2); left_s >= max(s - total / 2, 0);
             left_s--) {
          int res = 0;
          for (int k = max(c - left2, 0); k <= min(c, left1) && k * i <= left_s;
               k++) {
            res = (res + f[left1 - k][left_s - k * i] * INV_F[k] % MOD *
                             INV_F[c - k]) %
                  MOD;
          }
          f[left1][left_s] = res;
        }
      }
    }
    return F[n1] * F[n - n1] % MOD * f[n1][total / 2] % MOD;
  }
};