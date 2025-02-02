// solution 1
class Solution {
   public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        vector<int> tmp(nums.size() * 2, 0);
        for (int i = 0; i < 2 * n; i++) {
            tmp[i] = nums[i % n];
        }
        nums.clear();
        for (int i = 0, s = n - k; i < n; i++, s++) nums.push_back(tmp[s]);
    }
};