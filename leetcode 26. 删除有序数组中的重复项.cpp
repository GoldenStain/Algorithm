// solution 1
class Solution {
    public:
        int removeDuplicates(vector<int>& nums) {
            int k = 0;
            for(int i = 0; i < nums.size(); i++) {
                if (i == 0 || nums[i] != nums[i - 1]) 
                    nums[k++] = nums[i];
            }
            return k ;
        }
    };
// solution 2
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        std:vector<int>::iterator res = std::unique(nums.begin(), nums.end());
        nums.erase(res, nums.end());
        return res - nums.begin();
    }
};