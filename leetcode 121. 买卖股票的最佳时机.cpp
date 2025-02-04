class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int _min = 1e5, ans = 0;
        for(int i = 0; i < prices.size(); i++) {
            ans = std::max(ans, prices[i] - _min);
            _min = std::min(_min, prices[i]);
        }
        return ans;
    }
};