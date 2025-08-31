class Solution {
public:
  int minTaps(int n, vector<int> &ranges) {
    std::vector<int> right_bound(n + 1, 0);
    for (int i = 0; i < n + 1; i++) {
      int left = std::max(0, i - ranges[i]);
      right_bound[left] = std::max(right_bound[left], i + ranges[i]);
    }
    int cur_right = 0, next_right = 0, ans = 0;
    for (int i = 0; i < n; i++) {
      next_right = std::max(next_right, right_bound[i]);
      if (i == cur_right) {
        if (next_right < i + 1) {
          return -1;
        }
        cur_right = next_right;
        ans++;
      }
    }
    return ans;
  }
};