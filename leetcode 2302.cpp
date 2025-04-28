// first solution
class Solution {
public:
  long long countSubarrays(vector<int> &nums, long long k) {
    int n = nums.size();
    std::vector<long long> sums(n, 0);
    sums[0] = nums[0];
    for (int i = 1; i < n; i++) {
      sums[i] = sums[i - 1] + nums[i];
    }
    int hh = 0, tt = 0;
    long long ans = 0ll;
    for (; hh < n; hh++) {
      if (tt < hh)
        tt = hh;
      while (tt < n && subSum(sums, hh, tt) < k)
        tt++;
      tt--;
      if (tt >= hh)
        ans += tt - hh + 1;
    }
    return ans;
  }

private:
  inline long long subSum(std::vector<long long> &sums, int hh, int tt) {
    if (hh == 0)
      return sums[tt] * (tt + 1);
    return (sums[tt] - sums[hh - 1]) * (tt - hh + 1);
  }
};
