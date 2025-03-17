using std::cin, std::cout;
using std::vector;
class Solution {
   public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> stk;
        int ans = 0, n = heights.size();
        vector<int> left(n, -1), right(n, n); // -1和n对应边界情况
        for (int i = 0; i < n; i++) {
            while(stk.size() && heights[i] < heights[stk.back()]) {
                right[stk.back()] = i;
                stk.pop_back();
            }
            if (stk.size()) left[i] = stk.back();
            stk.push_back(i);
        }
        for (int i = 0; i < n; i++)
            ans = std::max(ans, (right[i] - left[i] - 1) * heights[i]);
        return ans;
    }
};