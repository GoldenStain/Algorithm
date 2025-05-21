class Solution {
public:
  bool isZeroArray(vector<int> &nums, vector<vector<int>> &queries) {
    // 差分不能原地进行，所以我们需要另外开辟一个数组
    std::vector<int> diff = nums;
    int n = nums.size(), q = queries.size();
    // 差分
    for (int i = 1; i < n; i++) {
      diff[i] = nums[i] - nums[i - 1];
    }
    for (int i = 0; i < q; i++) {
      int l = queries[i][0], r = queries[i][1];
      diff[l] -= 1;
      if (r + 1 < n)
        diff[r + 1] += 1;
    }
    // 可能数组只有一个元素，那么下面的循环就不会执行，所以这里要特判一下。
    if (diff[0] > 0)
      return false;
    // 还原
    for (int i = 1; i < n; i++) {
      diff[i] += diff[i - 1];
      if (diff[i] > 0)
        return false;
    }
    return true;
  }
};