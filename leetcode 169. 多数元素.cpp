class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int cnt = 1, ans = nums[0];
        for(int i = 1; i < nums.size(); i++) {
            if (nums[i] != ans) {
                cnt--;
                if(cnt == 0) {
                    ans = nums[i];
                    cnt = 1;
                }
            }
            else 
                cnt++;
        }
        return ans;
    }
};