class Solution {
    using VecInt = vector<int>;
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        vector<VecInt> ans{};
        int n = points.size();
        sort(points.begin(), points.end(), cmp);
        int st = INT_MIN, ed = INT_MIN;
        for (int i = 0; i < n; i++) {
            if (points[i][0] > ed) {
                if (st != INT_MIN)
                    ans.emplace_back(VecInt{st, ed});
                st = points[i][0]; 
                ed = points[i][1];
            }
            else
                ed = min(ed, points[i][1]);
        }
        return ans.size() + 1;
    }
    static bool cmp(VecInt &a, VecInt &b) {
        return a[0] < b[0];
    }
};