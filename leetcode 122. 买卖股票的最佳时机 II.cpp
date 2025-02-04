// solution 1
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        std::vector<std::vector<int>> f(n, std::vector<int>(2, 0));
        f[0][1] = -prices[0];
        for(int i = 1; i < n; i++) {
            f[i][0] = std::max(f[i - 1][0], f[i - 1][1] + prices[i]);
            f[i][1] = std::max(f[i - 1][0] - prices[i], f[i - 1][1]);
        }
        return std::max(f[n - 1][0], f[n - 1][1]);
    }
};

// solution 2
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int _no = 0, _has = -prices[0];
        for(int i = 1; i < n; i++) {
            _has = std::max(_has, _no - prices[i]);
            _no = std::max(_has + prices[i], _no);
        }
        return std::max(_has, _no);
    }
};