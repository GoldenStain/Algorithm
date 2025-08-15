
class Solution {
public:
  int findMin(vector<int> &nums) {
    int n = nums.size();
    // judge the corner case first.
    if (n == 1 || nums[0] < nums[n - 1]) {
      return nums[0];
    }
    int l = 0, r = n - 1, ans = -1;
    while (l <= r) {
      int mid = (l + r) >> 1;
      if (nums[mid] > nums[mid + 1]) {
        ans = nums[mid + 1];
        break;
      }
      if (nums[mid] >= nums[0]) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    return ans;
  }
};