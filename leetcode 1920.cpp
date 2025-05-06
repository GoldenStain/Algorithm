class Solution {
public:
  vector<int> buildArray(vector<int> &nums) {
    int n = nums.size();
    // 记录信息
    // 1000进制下的表示：(nums[nums[i]])(nums[i])，目标信息在高位上
    for (int i = 0; i < n; i++) {
      // 注意要取模，因为nums[nums[i]]可能已经是我们修改过的值，不取模的话多次运算后会溢出
      nums[i] += 1000 * (nums[nums[i]] % 1000);
    }
    // 取出目标信息
    for (int i = 0; i < n; i++)
      nums[i] /= 1000;
    return nums;
  }
};