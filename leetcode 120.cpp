class Solution {
   public:
    int minimumTotal(vector<vector<int>> &triangle) {
        int n = triangle.size();
        vector<vector<int>> f(2, vector<int>(n, 100000000));
        int idx;
        // 设置边界条件
        for (int i = 0; i < n; i++) f[(n - 1) & 1][i] = triangle[n - 1][i];
        for (int i = n - 2; i >= 0; i--) {
            idx = i & 1;
            for (int j = 0; j <= i; j++) {
                f[idx][j] = std::min(f[idx ^ 1][j] + triangle[i][j],
                                     f[idx ^ 1][j + 1] + triangle[i][j]);
            }
        }
        return f[idx][0];
    }
};