class Solution {
   public:
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> f(n, vector<int>(m, 400 * 400));
        // 第一行
        for (int i = 0; i < m; i++)
            f[0][i] = i == 0 ? grid[0][i] : f[0][i - 1] + grid[0][i];
        // 第一列
        for (int i = 0; i < n; i++)
            f[i][0] = i == 0 ? grid[i][0] : f[i - 1][0] + grid[i][0];
        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++)
                f[i][j] = std::min(f[i - 1][j], f[i][j - 1]) + grid[i][j];
        return f[n - 1][m - 1];
    }
};