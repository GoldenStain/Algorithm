class Solution {
public:
  int lengthOfLIS(vector<int> &nums) {
    if (nums.size() == 1) {
      return 1;
    }
    int n = nums.size();
    vector<int> ups;
    ups.push_back(nums[0]);
    for (int i = 1; i < n; i++) {
      if (nums[i] > ups.back()) {
        ups.emplace_back(nums[i]);
      } else {
        auto pos = std::lower_bound(ups.begin(), ups.end(), nums[i]);
        std::cout << pos - ups.begin();
        *pos = nums[i];
      }
    }
    return ups.size();
  }
};