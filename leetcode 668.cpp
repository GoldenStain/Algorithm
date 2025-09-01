class Solution {
public:
  int findKthNumber(int m, int n, int k) {
    int left = 1, right = m * n;
    auto check = [&](int x) -> bool {
      int bound = x / n, cnt = bound * n;
      for (int i = bound + 1; i <= m; i++)
        cnt += x / i;
      return cnt >= k;
    };
    while (left < right) {
      int mid = (left + right) >> 1;
      if (check(mid))
        right = mid;
      else
        left = mid + 1;
    }
    return left;
  }
};