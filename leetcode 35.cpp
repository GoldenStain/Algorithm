class Solution {
public:
  int searchInsert(vector<int> &nums, int target) {
    int len = nums.size();
    if (nums[len - 1] < target) {
      return len;
    }
    int l = 0, r = len - 1;
    // 最左边的>=target的
    while (l < r) {
      int mid = (l + r) >> 1;
      if (nums[mid] >= target) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    // 如果存在，那么就是l
    // 如果不存在，那么他会插入到nums[l]的前面，顶替l的下标.
    return l;
  }
};