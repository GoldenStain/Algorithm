class Solution {
   public:
    int minMoves(vector<int>& nums, int k) {
        int n = nums.size();
        std::vector<int> g, preSum;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 1) {
                g.emplace_back(i - g.size());
                if (preSum.empty()) {
                    preSum.emplace_back(g.back());
                } else {
                    preSum.emplace_back(preSum.back() + g.back());
                }
            }
        }
        n = g.size();
        int ans = -1;
        for (int i = 0; i + k <= n; i++) {
            int now, _end = i + k - 1, mid = (i + _end) >> 1;
            if (k & 1) {
                now = getPreSum(preSum, mid + 1, _end) -
                      getPreSum(preSum, i, mid - 1);
            } else
                now = getPreSum(preSum, mid + 1, _end) -
                      getPreSum(preSum, i, mid - 1) - g[mid];
            ans = inline_min(ans, now);
        }
        return ans;
    }
    inline int getPreSum(vector<int>& preSum, int l, int r) {
        if (l > r) return 0;
        if (l == 0) {
            return preSum[r];
        }
        return preSum[r] - preSum[l - 1];
    }
    inline int inline_min(int a, int b) {
        if (a < 0)
            return b;
        else
            return std::min(a, b);
    }
};