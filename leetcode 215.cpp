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
    if (i > k)
      return worker(nums, l, i - 1, k);
    else
      return worker(nums, i, r, k);
  }
};