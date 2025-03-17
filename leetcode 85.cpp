class Solution {
    public:
     int maximalRectangle(vector<vector<char>>& matrix) {
         int m = matrix.size(), n = matrix[0].size();
         vector<vector<int>> ones(m, vector<int>(n, 0));
         for (int i = 0; i < m; i++) {
             for (int j = 0; j < n; j++) {
                 if (matrix[i][j] == '1') {
                     ones[i][j] = (j==0?0:ones[i][j - 1]) + 1;
                 }
             }
         }// 预处理完毕
         std::vector<int> stk, up, down;
         int ans = 0;
         for (int j = 0; j < n; j++) {
             stk.clear();
             up.assign(m, -1);
             down.assign(m, m);
             for (int i = 0; i < m; i++) {
                 while (stk.size() && ones[i][j] < ones[stk.back()][j]) {
                     down[stk.back()] = i;
                     stk.pop_back();
                 }
                 if (stk.size())
                     up[i] = stk.back();
                 stk.push_back(i);
             }
             for (int i = 0; i < m; i++) {
                 int width = down[i] - up[i] - 1;
                 ans = std::max(ans, width * ones[i][j]);
             }
         }
         return ans;
     }
 };