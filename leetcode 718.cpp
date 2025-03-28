class Solution {
    using VecInt = vector<int>;

   public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
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
// DP solution
class Solution {
   public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        vector<vector<int>> dp(n1, vector<int>(n2, 0));
        int ans = 0;
        // dp[i][j]表示：以i、j结尾的最长重复字串
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                if (nums1[i] == nums2[j]) {
                    if (i && j) {
                        dp[i][j] = std::max(dp[i][j], dp[i - 1][j - 1] + 1);
                    } else {
                        dp[i][j] = 1;
                    }
                }
                ans = std::max(ans, dp[i][j]);
            }
        }
        return ans;
    }
};

// binary-search solution
class Solution {
    typedef unsigned long long ULL;
    static constexpr ULL base = 113;

   public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        vector<ULL> hash1(n1, 0), hash2(n2, 0);
        initHash(nums1, hash1);
        initHash(nums2, hash2);
        // 一开始左边界设置错了，把l设置为1；要注意最坏情况应该是没有公共元素，所以l应该设置为0.
        int l = 0, r = std::min(n1, n2);
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (check(nums1, hash1, nums2, hash2, mid)) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        return l;
    }
    void initHash(vector<int>& n, vector<ULL>& hash) {
        hash[0] = (ULL)n[0];
        for (int i = 1; i < n.size(); i++) {
            hash[i] = hash[i - 1] * base + (ULL)n[i];
        }
    }

    ULL qPow(ULL base, int len) {
        ULL res = 1;
        while (len) {
            if (len & 1) {
                res *= base;
            }
            base *= base;
            len >>= 1;
        }
        return res;
    }

    ULL query(vector<ULL>& hash, int l, int r) {
        if (l == 0) {
            return hash[r];
        }
        return hash[r] - hash[l - 1] * qPow(base, r - l + 1);
    }

    bool check(vector<int>& nums1, vector<ULL>& hash1, vector<int>& nums2,
               vector<ULL>& hash2, int len) {
        std::unordered_set<ULL> in_nums1, in_nums2;
        for (int i = 0; i + len <= nums1.size(); i++) {
            in_nums1.insert(query(hash1, i, i + len - 1));
        }
        for (int i = 0; i + len <= nums2.size(); i++) {
            ULL query_res = query(hash2, i, i + len - 1);
            if (in_nums1.find(query_res) != in_nums1.end()) {
                return true;
            }
        }
        return false;
    }
};