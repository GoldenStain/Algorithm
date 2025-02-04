class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size(), last_reachable = n - 1;
        for(int i = n - 2;i >= 0; i--) {
            last_reachable = i + nums[i] >= last_reachable ? i : last_reachable;
        }
        return last_reachable == 0;
    }
};