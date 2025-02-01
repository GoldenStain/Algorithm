// solution 1
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        std:vector<int>::iterator res = std::unique(nums.begin(), nums.end());
        nums.erase(res, nums.end());
        return res - nums.begin();
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