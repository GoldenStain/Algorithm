class Solution {
    public:
        void setZeroes(vector<vector<int>>& matrix) {
            bool col_0 = false;
            int m = matrix.size(), n = matrix[0].size();
            for (int i = 0; i < m; i++) {
                // 这个要放在前面，因为后面可能的matrix[i][j]可能会把matrix[i][0]置为0
                if (!matrix[i][0])
                    col_0 = true;
                // 因为第一列单独统计，所以这个循环从1开始。
                // 只有i=0的时候，才能把matrix[0][0]置为0，所以说“第一列的第一个元素即可以标记第一行是否出现 0”
                for (int j = 1; j < n; j++) {
                    if (!matrix[i][j])
                        matrix[i][0] = matrix[0][j] = 0;
                }
            }
            for (int i = m - 1; i >= 0; i--) {
                // 同样地，第一列单独处理，所以循环从1开始
                for (int j = 1; j < n; j++) {
                    // 到了第一行的时候，i=0,只有matrix[0][0]=0，才会把这一行统一置为0，再次印证了“第一列的第一个元素即可以标记第一行是否出现 0”
                    if (!matrix[i][0] || !matrix[0][j])
                        matrix[i][j] = 0;
                }
                if (col_0)
                    matrix[i][0] = 0;
            }
        }
    };