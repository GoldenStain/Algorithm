class Solution {
public:
  int minimizeMax(vector<int> &nums, int p) {
    int n = nums.size();
    std::sort(nums.begin(), nums.end());
    int l = 0, r = nums.back() - nums.front();
    auto check = [&](int threshold) -> bool {
      int cnt = 0;
      for (int i = 0; i < n - 1; i++) {
        if (nums[i + 1] - nums[i] <= threshold) {
          cnt++;
          // 能够满足条件就多走一步，防止重复选取一个数
          i++;
        }
      }
      return cnt >= p;
    };
    while (l < r) {
      int mid = (l + r) >> 1;
      if (check(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return l;
  }
};