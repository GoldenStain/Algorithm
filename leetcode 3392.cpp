class Solution {
public:
  int countSubarrays(vector<int> &nums) {
    int n = nums.size();
    int hh = 0, tt = 0, ans = 0;
    for (; tt < n; tt++) {
      while (tt - hh > 2) {
        hh++;
      }
      if (tt - hh == 2 && check(nums[hh], nums[hh + 1], nums[hh + 2]))
        ans++;
    }
    return ans;
  }

private:
  bool check(int a, int b, int c) { return ((a + c)) << 1 == b; }
};