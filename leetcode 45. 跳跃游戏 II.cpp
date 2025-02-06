class Solution {
    using two_d_vec = std::vector<std::vector<int> >;

   public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        // 这里可以开到Log(1000)压空间
        std::vector<std::vector<int> > f(n, std::vector<int>(16, 1e5));
        std::vector<int> _log(n + 1, 0);
        f[n - 1][0] = 0;
        _log[1] = 0;
        for (int i = n - 2; i >= 0; i--) {
            int len = n - i;
            _log[len] = _log[len >> 1] + 1;
            f[i][0] = query(f, _log, i + 1, std::min(n - 1, i + nums[i])) + 1;
            // 一开始循环条件中有一个 && (1 << j) < nums[i]，
            // 这样是不行的，因为有可能nums[i]很小,nums[i - 1]却很大，i -
            // 1会需要后面的信息。
            for (int j = 1; i + (1 << j) - 1 < n; j++) {
                f[i][j] = std::min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
            }
        }
        return f[0][0];
    }

   private:
    int query(two_d_vec& f, std::vector<int>& _log, int l, int r) {
        if (r < l) return 1e5;
        int len = _log[r - l + 1];
        return std::min(f[l][len], f[r - (1 << len) + 1][len]);
    }
};

// 贪心

class Solution {
   public:
    int jump(vector<int>& nums) {
        int max_reachable = 0, end = 0, step = 0;
        for (int i = 0; i < nums.size() - 1; i++) {
            if (max_reachable >= i)
                max_reachable = std::max(max_reachable, i + nums[i]);
            if (i == end) {
                end = max_reachable;
                step++;
            }
        }
        return step;
    }
};