// 双指针
class Solution {
public:
  long long countFairPairs(vector<int> &nums, int lower, int upper) {
    std::sort(nums.begin(), nums.end());
    int n = nums.size();
    int right_bound = n - 1, left_bound = n - 1;
    long long ans = 0ll;
    for (int i = 0; i < n; i++) {
      int A = lower - nums[i], B = upper - nums[i];
      while (right_bound && nums[right_bound - 1] > B)
        right_bound--;
      while (left_bound && nums[left_bound - 1] >= A)
        left_bound--;
      // 最后合法区间是[left, right)
      // 我们要保证不会重复，免得同一对数字被重复计算
      // 这个取min操作既避免了我们把nums[i]本身统计进来，也能避免重复
      ans += (long long)(std::min(right_bound, i) - std::min(left_bound, i));
    }
    return ans;
  }
};

// 二分
class Solution {
public:
  long long countFairPairs(vector<int> &nums, int lower, int upper) {
    std::sort(nums.begin(), nums.end());
    int n = nums.size();
    long long ans = 0;
    for (int i = 0; i < n; i++) {
      int B = upper - nums[i], A = lower - nums[i];
      std::vector<int>::iterator right_bound = std::upper_bound(
                                     nums.begin(), nums.begin() + i, B),
                                 left_bound = std::lower_bound(
                                     nums.begin(), nums.begin() + i, A);
      // 同样地，要避免重复
      ans += (long long)(right_bound - left_bound);
    }
    return ans;
  }
};