class Solution {
    public:
        void gameOfLife(vector<vector<int>>& board) {
            int m = board.size(), n = board[0].size();
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    int live = 0;
                    for(int x = i - 1; x <= i + 1; x++) {
                        for (int y = j - 1; y <= j + 1; y++) {
                            if (x <0 || x >= m || y <0 || y >= n || (x == i && y == j))
                                continue;
                            live += std::abs(board[x][y]) == 1;
                        } // y
                    }// x
                    if (board[i][j] == 1 && (live < 2 || live > 3))
                        board[i][j] = -1;
                    else if (board[i][j] == 0 && live == 3)
                        board[i][j] = 2;
                }// j
            }// i
            for (int i = 0; i < m; i++)
                for(int j = 0; j < n; j++)
                    if (board[i][j] > 0)
                        board[i][j] = 1;
                    else
                        board[i][j] = 0;
        }
    };