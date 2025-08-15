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