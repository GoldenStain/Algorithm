using PII = std::pair<int, int>;
class Solution {
public:
  int findPeakElement(vector<int> &nums) {
    int n = nums.size();
    // 因为题目给定的数据范围直接把int用光了
    // 所以我们可以另辟蹊径来比较大小
    std::function<PII(int)> get = [&](int pos) -> PII {
      if (pos == -1 || pos == n) {
        return {0, 0};
      }
      return {1, nums[pos]};
    };
    int l = 0, r = n - 1;
    int ans = -1;
    // 这里加上l==r的情况，是为了涵盖到最后一步正好找到答案的case，如果不包括l==r，就会错过答案。
    while (l <= r) {
      int mid = (l + r) >> 1;
      if (get(mid) > get(mid + 1) && get(mid) > get(mid - 1)) {
        ans = mid;
        break;
      } else if (get(mid) < get(mid + 1)) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    return ans;
  }
};