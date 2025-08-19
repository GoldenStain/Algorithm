namespace leetcode {
template <typename T> using vector = std::vector<T>;
template <typename T> using function = std::function<T>;

using PII = std::pair<int, int>;

constexpr int N = 2e5 + 2;

int n;
std::array<int, N> a{}, b{}, less_or_equal_right{};

inline int lowbit(int x) { return x & (-x); }
struct TreeArr {
  int upper;
  std::vector<int> arr;
  TreeArr(int _upper) : upper(_upper) { arr.resize(upper + 1); }

  int query(int pos) {
    int res = 0;
    while (pos) {
      res += arr[pos];
      pos -= lowbit(pos);
    }
    return res;
  }

  void update(int pos, int x) {
    while (pos <= upper) {
      arr[pos] += x;
      pos += lowbit(pos);
    }
  }
};

class Solution {
public:
  void solve() {
    freopen("input.txt", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
      std::cin >> a[i];
    }
    // 离散化
    std::vector<int> tmp(a.begin(), a.end());
    std::sort(tmp.begin(), tmp.end());
    tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());

    for (int i = 1; i <= n; i++) {
      b[i] = (std::lower_bound(tmp.begin(), tmp.end(), a[i]) - tmp.begin()) + 1;
    }

    long long ans = 0;
    TreeArr backward_tree = TreeArr(tmp.size() + 1);
    for (int i = n; i >= 1; i--) {
      int cnt = backward_tree.query(b[i] - 1);
      less_or_equal_right[i] = backward_tree.query(b[i]);
      ans += static_cast<long long>(cnt) * (cnt - 1) / 2;
      backward_tree.update(b[i], 1);
    }
    TreeArr forward_tree = TreeArr(tmp.size() + 1);
    for (int i = 1; i <= n; i++) {
      int cnt = i - 1 - forward_tree.query(b[i]);
      ans -= static_cast<long long>(cnt) * less_or_equal_right[i];
      forward_tree.update(b[i], 1);
    }
    std::cout << ans << std::endl;
  }
};
} // namespace leetcode
