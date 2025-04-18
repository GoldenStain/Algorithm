class Solution {
   public:
    int removeDuplicates(vector<int>& nums) {
        int k = 0, cnt = 0;
        for (int i = 0; i <= nums.size(); i++) {
            if (!i || i == nums.size() || nums[i] != nums[i - 1]) {
                for (int j = 0; j < min(cnt, 2); j++) nums[k++] = nums[i - 1];
                cnt = 1;
            } else if (nums[i] == nums[i - 1])
                cnt++;
        }
        return k;
    }
};

// solution 2
class Solution {
    public:
        int removeDuplicates(vector<int>& nums) {
            int cnt = 0, k = 0;
            for(int i = 0; i < nums.size(); i++) {
                if (!i || nums[i] == nums[i - 1])
                    cnt++;
                else {
                    for(int j = 0; j < min(cnt, 2); j++) {
                        nums[k++] = nums[i - 1];
                    }
                    cnt = 1;
                }
            }
            for (int j = 0; j < min(cnt, 2); j++)
                nums[k++] = nums[nums.size() -1];
            return k;
        }
    };