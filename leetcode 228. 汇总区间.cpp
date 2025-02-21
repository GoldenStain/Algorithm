class Solution {
    public:
        vector<string> summaryRanges(vector<int>& nums) {
            if (nums.size() == 0)
                return vector<string>();
            std::string res = "";
            vector<string> ans;
            int st = nums[0];
            for(int i = 1; i < nums.size(); i++) {
                if (nums[i] != nums[i - 1] + 1)
                 {
                    res = to_string(st);
                    if (nums[i - 1] != st) {
                        res += "->";
                        res += to_string(nums[i - 1]);
                    }
                    st = nums[i];
                    ans.emplace_back(res);
                }
            }
            res = to_string(st);
            if (nums[nums.size() - 1] != st) {
                res += "->";
                res += to_string(nums[nums.size() - 1]);
            }
            ans.emplace_back(res);
            return ans;
        }
    };