class Solution {
   public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        std::sort(nums.begin(), nums.end());
        nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
        int hh = 0, tt = 0, res = n + 1;
        for (; hh < nums.size(); hh++) {
            int right = nums[hh] + n - 1;
            while (tt < nums.size() && nums[tt] <= right) {
                tt++;
            }
            tt--;
            res = std::min(res, n - (tt - hh + 1));
        }
        return res;
    }
};
