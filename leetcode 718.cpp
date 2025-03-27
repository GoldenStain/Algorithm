class Solution {
    using VecInt = vector<int>;
   public:
    int findLength(vector<int> &nums1, vector<int> &nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        int ans = 0;
        // 移动nums1
        for (int i = 0; i < n1; i++) {
            ans = std::max(ans, getAns(nums1, i, nums2, 0));
        }
        // 移动nums2
        for (int i = 0; i < n2; i++) {
            ans = std::max(ans, getAns(nums1, 0, nums2, i));
        }
        return ans;
    }
    int getAns(VecInt& a, int oa, VecInt& b, int ob) {
        int len = std::min(a.size() - oa, b.size() - ob), res = 0;
        // 需要两个变量来配合统计，如果只用一个变量，那么后面的更小重复字串可能会覆盖前面更长的重复字串，导致我们丢失正确答案。
        int now_len = 0;
        for (int i = 0; i < len; i++) {
            char ca = a[oa + i], cb = b[ob + i];
            if (ca == cb)
                now_len++;
            else {
                res = std::max(res, now_len);
                now_len = 0;
            }
            // 可能最后一截也是相等的，上面的逻辑不会涉及这个判断。
            res = std::max(res, now_len);
        }
        return res;
    }
};
