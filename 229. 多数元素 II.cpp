// wrong solution
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int cnt1 = 1, cnt2 = 1;
        int ans1 = nums[0], ans2 = ans1;
        for(int i = 1; i <nums.size(); i++) {
            if (nums[i] == ans1)
                cnt1++;
            else if (ans1 == ans2) {
                cnt2 = 1;
                ans2 = nums[i];
                std::cout << "new ans2: " << ans2 << std::endl;
            }
            else if (nums[i] == ans2)
                cnt2++;
            else {
                cnt1--;
                cnt2--;
                if(cnt1 <= 0)
                    cnt1 = 1, ans1 = nums[i], std::cout << "new ans1: " << ans1 << std::endl;
                if(cnt2 <= 0)
                    cnt2 = 1, ans2 = nums[i], std::cout << "new ans2: " << ans2 << std::endl;
            }
        }
        cnt1 =0; cnt2 = 0;
        for(int i = 0; i < nums.size(); i++) {
            if (nums[i] == ans1)
                cnt1++;
            else if (nums[i] == ans2)
                cnt2++;
        }
        int n = nums.size();
        nums.clear();
        if(cnt1 > n/3)
            nums.push_back(ans1);
        if(cnt2 > n/3 && ans2 != ans1)
            nums.push_back(ans2);
        return nums;
}};

// right solution

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int cnt1 = 0, cnt2 = 0;
        int ans1 = nums[0], ans2 = ans1;
        for(int i = 0; i <nums.size(); i++) {
            if (cnt1 && nums[i] == ans1)
                cnt1++;
            else if (cnt2 && nums[i] == ans2)
                cnt2++;
            else if (cnt1 == 0 )
                cnt1++, ans1 = nums[i];
            else if (cnt2 == 0)
                cnt2++, ans2 = nums[i];
            else
                cnt1--, cnt2--;
        }
        cnt1 =0; cnt2 = 0;
        for(int i = 0; i < nums.size(); i++) {
            if (nums[i] == ans1)
                cnt1++;
            else if (nums[i] == ans2)
                cnt2++;
        }
        int n = nums.size();
        nums.clear();
        if(cnt1 > n/3)
            nums.push_back(ans1);
        if(cnt2 > n/3)
            nums.push_back(ans2);
        return nums;
}};