// 无论目标值是否存在，lower_bound和upper_bound返回结果都是：第一个大于等于target的索引、第一个大于target的索引
class Solution {
public:
  vector<int> searchRange(vector<int> &nums, int target) {
    vector<int> ans;
    vector<int>::iterator lower_iter =
        std::lower_bound(nums.begin(), nums.end(), target);
    if (lower_iter == nums.end() || *lower_iter != target) {
      ans = {-1, -1};
    } else {
      auto upper_iter = std::upper_bound(nums.begin(), nums.end(), target) - 1;
      ans = {static_cast<int>(lower_iter - nums.begin()),
             static_cast<int>(upper_iter - nums.begin())};
    }
    return ans;
  }
};
// hand-write version
class Solution {
public:
  vector<int> searchRange(vector<int> &nums, int target) {
    vector<int> ans;
    nums.push_back(INT_MAX);
    int n = nums.size();
    function<int()> find_lower = [&]() -> int {
      int l = 0, r = n - 1;
      while (l < r) {
        int mid = (l + r) >> 1;
        if (nums[mid] >= target) {
          r = mid;
        } else {
          l = mid + 1;
        }
      }
      return l;
    };
    function<int()> find_upper = [&]() -> int {
      int l = 0, r = n - 1;
      while (l < r) {
        int mid = (l + r) >> 1;
        if (nums[mid] > target) {
          r = mid;
        } else {
          l = mid + 1;
        }
      }
      return l;
    };
    int lower_pos = find_lower();
    if (lower_pos == n || nums[lower_pos] != target) {
      ans = {-1, -1};
    } else {
      int upper_pos = find_upper();
      ans = {lower_pos, upper_pos - 1};
    }
    return ans;
  }
};