class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> ans(n, 0);
        ans[0] = 1;
        for(int i = 1; i < n; i++)
            ans[i] = ans[i - 1] * nums[i - 1];
        int R = 1;
        for(int i = n - 1; i >= 0; i--) {
            ans[i] = ans[i] * R;
            R *= nums[i];
        }
        return ans;
    }
};