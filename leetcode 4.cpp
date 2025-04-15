class Solution {
public:
  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    int n1 = nums1.size(), n2 = nums2.size();
    if ((n1 + n2) % 2 == 0)
      return ((double)findKthEle(nums1, nums2, (n1 + n2) / 2) +
              (double)findKthEle(nums1, nums2, (n1 + n2) / 2 + 1)) /
             2;
    else
      return (double)findKthEle(nums1, nums2, (n1 + n2 + 1) / 2);
  }
  int findKthEle(vector<int> &nums1, vector<int> &nums2, int k) {
    int l1 = 0, l2 = 0;
    while (k > 1 && l1 < nums1.size() && l2 < nums2.size()) {
      // 注意不能超过了nums1或者nums2还剩下元素的个数
      int k1 = std::min(k >> 1, static_cast<int>(nums1.size() - l1));
      int k2 = std::min(k - k1, static_cast<int>(nums2.size() - l2));
      if (nums1[l1 + k1 - 1] <= nums2[l2 + k2 - 1]) {
        k -= k1;
        l1 = l1 + k1;
      } else {
        k -= k2;
        l2 = l2 + k2;
      }
    }
    // 这里也要小心访问到越界的值
    int x1 = (l1 < nums1.size()) ? nums1[l1 + k - 1] : 1e7,
        x2 = (l2 < nums2.size()) ? nums2[l2 + k - 1] : 1e7;
    return std::min(x1, x2);
  }
};