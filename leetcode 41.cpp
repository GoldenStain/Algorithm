class Solution {
   public:
    static constexpr int L = 1e6;
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] <= 0) {
                nums[i] = L;
            }  // 先排除负数的干扰
        }
        for (int i = 0; i < n; i++) {
            int x = std::abs(nums[i]);
            if (x <= n) {
                nums[x - 1] = -std::abs(nums[x - 1]);
            }
        }
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) return i + 1;
        }
        return n + 1;
    }
};