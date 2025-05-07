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

// mathematical solution
class Solution {
public:
  vector<int> buildArray(vector<int> &nums) {
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      if (nums[i] < 0)
        continue;
      int cur = i, nxt, x = nums[i];
      while (nums[cur] != i) {
        nxt = nums[cur];
        nums[cur] = ~nums[nxt];
        cur = nxt;
      }
      // 置换环上最后一个位置，首尾相接
      nums[cur] = ~x;
    }
    for (int i = 0; i < n; i++)
      nums[i] = ~nums[i];
    return nums;
  }
};
