class Solution {
public:
  int maximumDifference(vector<int> &nums) {
    int n = nums.size();
    int ans = -1;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++)
        ans = (nums[i] < nums[j]) ? std::max(ans, nums[j] - nums[i]) : ans;
    }
    return ans;
  }
};