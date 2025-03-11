// 交换写法
class Solution {
    public:
        vector<vector<int>> ans;
        vector<vector<int>> permute(vector<int>& nums) {
            int n = nums.size();
            dfs(nums, 0, n);
            return ans;
        }
        void dfs(vector<int>& nums, int now, int len) {
            if (now == len) {
                ans.emplace_back(nums);
                return;
            }
            for(int i = now; i < len; i++) {
                std::swap(nums[i], nums[now]);
                dfs(nums, now + 1, len);
                std::swap(nums[i], nums[now]);
            }
        }
    };

// 选择写法
class Solution {
    public:
        using VecInt = std::vector<int>;
        std::vector<VecInt> ans;
        vector<vector<int>> permute(vector<int>& nums) {
            int n = nums.size();
            std::vector<bool> flag(n, false);
            std::vector<int> arr;
            dfs(nums, arr, 0, n, flag);
            return ans;
        }
        void dfs(VecInt& nums, VecInt& arr, int now, int len, std::vector<bool>& flag) {
            if (now == len) {
                ans.emplace_back(arr);
                return;
            }
            for(int i = 0; i < len; i++) {
                if (flag[i])
                    continue;
                arr.emplace_back(nums[i]);
                flag[i] = true;
                dfs(nums, arr, now + 1, len, flag);
                arr.pop_back();
                flag[i] = false;
            }
        }
    };