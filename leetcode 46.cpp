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
        for (int i = now; i < len; i++) {
            // 虽然now和now交换是无效交换，但这里i还是要从now开始，如果不从now开始的话：
            // 当now = len - 1的时候，这个循环就没有事情做了
            // 这个循环没有事情做，就不会触发内部的dfs(now+1)
            // 我们就不会到达now == len，就不会统计答案了。
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
    void dfs(VecInt& nums, VecInt& arr, int now, int len,
             std::vector<bool>& flag) {
        if (now == len) {
            ans.emplace_back(arr);
            return;
        }
        for (int i = 0; i < len; i++) {
            if (flag[i]) continue;
            arr.emplace_back(nums[i]);
            flag[i] = true;
            dfs(nums, arr, now + 1, len, flag);
            arr.pop_back();
            flag[i] = false;
        }
    }
};