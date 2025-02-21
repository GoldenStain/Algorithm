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

// solution 2
class Solution {
    public:
        vector<string> summaryRanges(vector<int>& nums) {
            int n = nums.size();
            vector<string> ans;
            for(int i = 0; i < n; i++) {
                int j = i + 1;
                while(j < n && nums[j] == 1 + nums[j - 1]) 
                    j++;
                j--;
                std::string res = to_string(nums[i]);
                if (i < j) {
                    res += "->";
                    res += to_string(nums[j]);
                }
                ans.push_back(res);
                i = j;
            }
            return ans;
        }
    };