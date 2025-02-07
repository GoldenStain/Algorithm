// DP
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        std::vector<int> lmax(n, 0), rmax(n, 0);
        lmax[0] = height[0];
        rmax[n - 1] = height[n - 1];
        for(int i = 1; i < n; i++)
            lmax[i] = std::max(lmax[i - 1], height[i]);
        for(int i = n - 2; i >= 0; i--)
            rmax[i] = std::max(rmax[i + 1], height[i]);
        int ans = 0;
        for(int i = 1; i < n - 1; i++)
            ans += std::min(lmax[i], rmax[i]) - height[i];
        return ans;
    }
};

