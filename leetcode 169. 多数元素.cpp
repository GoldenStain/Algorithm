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

// 抵消思想写法
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int cnt = 0, ans = 0;
        for(int i = 0; i < nums.size(); i++) {
            if (cnt == 0)
                cnt++, ans = nums[i];
            else if (cnt > 0 && nums[i] == ans)
                cnt++;
            else cnt--;
        }
        return ans;
    }
};