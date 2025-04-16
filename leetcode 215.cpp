class Solution {
public:
  int findKthLargest(vector<int> &nums, int k) {
    int n = nums.size();
    return worker(nums, 0, n - 1, k - 1);
  }
  int worker(vector<int> &nums, int l, int r, int k) {
    if (l == r)
      return nums[k];
    int pivot = (l + r + 1) >> 1;
    pivot = nums[pivot];
    int i = l - 1, j = r + 1;
    while (i < j) {
      do {
        i++;
      } while (nums[i] > pivot);
      do {
        j--;
      } while (nums[j] < pivot);
      if (i < j)
        std::swap(nums[j], nums[i]);
    }
    // 当i >
    // k的时候，即i-1>=k,因为nums[0~i-1]>=pivot，所以下标为K的数字，一定在[l~i-1]当中
    // 这里一定要用i-1，不能用i；
    // 因为我们的哨兵选择的是nums[l+r+1>>1]，所以最后i不可能停在nums[l]，但是可能停在nums[r]，如果用(l,
    // i)，就会导致区间不缩小，进入死循环
    if (i > k)
      return worker(nums, l, i - 1, k);
    // 当i <= k的时候，即i-1 <
    // k，说明下标为K的数字，肯定在i-1右边，所以从i开始找，因为i一定不等于l，所以这个语句不会导致死循环
    else
      return worker(nums, i, r, k);
  }
};