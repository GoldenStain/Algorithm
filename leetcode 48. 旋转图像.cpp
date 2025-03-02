class Solution {
    public:
        void rotate(vector<vector<int>>& matrix) {
            int n = matrix.size();
            // 水平
            for(int i = 0; i < n/2; i++) {
                for (int j = 0; j < n; j++) {
                    std::swap(matrix[i][j],  matrix[n - 1 - i][j]);
                }
            }
            // 对角线
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < i; j++) 
                    std::swap(matrix[i][j], matrix[j][i]);
            }
            
        }
    };