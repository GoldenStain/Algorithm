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

// complex solution
class Solution {
public:
  long long countSubarrays(vector<int> &nums, long long k) {
    int n = nums.size();
    int hh = 0, tt = 0, cnt = 1;
    long long ans = 0ll, sum = nums[hh];
    for (; hh < n; hh++) {
      if (tt < hh) {
        tt = hh;
        sum = static_cast<long long>(nums[hh]);
      }
      while (tt < n) {
        cnt = tt - hh + 1;
        // 要小心当tt抵达数组末尾的时候，next_sum的计算会导致越界
        long long next_sum =
            (tt < n - 1)
                ? (((sum / cnt) + static_cast<long long>(nums[tt + 1])) *
                   (cnt + 1))
                : (k + 1);
        if (next_sum < k) {
          sum = next_sum;
          tt++;
        } else
          break;
      }
      cnt = tt - hh + 1;
      // 记得加判定条件，防止加上了非法值
      if (sum < k)
        ans += cnt;
      sum = ((sum / cnt) - static_cast<long long>(nums[hh])) * (cnt - 1);
    }
    return ans;
  }
};
