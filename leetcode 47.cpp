// dfs with vis array as marker
class Solution {
public:
  vector<vector<int>> permuteUnique(vector<int> &nums) {
    std::sort(nums.begin(), nums.end());
    int n = nums.size();
    std::vector vis(n, false);
    std::vector<std::vector<int>> ans;
    std::vector<int> tmp(n);
    auto permuteAll = [&](this auto &self, int step) -> void {
      if (step == n) {
        ans.push_back(tmp);
        return;
      }
      for (int i = 0; i < n; i++) {
        if (vis[i] || (i && (nums[i] == nums[i - 1] && !vis[i - 1])))
          continue;
        vis[i] = true;
        tmp[step] = nums[i];
        self(step + 1);
        vis[i] = false;
      }
    };
    permuteAll(0);
    return ans;
  }
};

// hashtable solution
class Solution {
public:
  vector<vector<int>> permuteUnique(vector<int> &nums) {
    int n = nums.size();
    std::unordered_map<int, int> um;
    for (int i = 0; i < n; i++)
      um[nums[i]]++;
    std::vector<std::vector<int>> ans;
    std::vector<int> tmp(n);
    auto permuteAll = [&](this auto &self, int step) -> void {
      if (step == n) {
        ans.push_back(tmp);
        return;
      }
      // 这里要记得用引用，否则map本身的值不会改变
      for (auto &pair : um) {
        if (pair.second == 0)
          continue;
        pair.second--;
        tmp[step] = pair.first;
        self(step + 1);
        pair.second++;
      }
    };
    permuteAll(0);
    return ans;
  };
};