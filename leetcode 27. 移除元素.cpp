// solution 1
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        return std::remove(nums.begin(), nums.end(), val) - nums.begin();
    }
};

// solution 2
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int pos = nums.size() - 1;
        for(int i = 0; i <= pos; i++) {
            while(i <= pos && nums[i] == val) {
                std::swap(nums[i], nums[pos--]);
            }
        }
        return pos + 1;
    }
};

// solution 3
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int pos = nums.size() - 1, i = pos;
        while(i >= 0) {
            if (nums[i] == val)
                std::swap(nums[i], nums[pos--]);
            i--;
        }
        return pos + 1;
    }
};
