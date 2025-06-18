class Solution {
public:
  vector<vector<int>> divideArray(vector<int> &nums, int k) {
    int n = nums.size();
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> ans;
    for (int i = 0; i + 3 <= n; i += 3) {
      if (nums[i + 2] - nums[i] > k) {
        ans.clear();
        return ans;
      }
      std::vector<int> tmp = {nums[i], nums[i + 1], nums[i + 2]};
      ans.emplace_back(tmp);
    }
    return ans;
  }
};