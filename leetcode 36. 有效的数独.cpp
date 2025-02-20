class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int init_v = (1 << 10) - 1;
        // 1表示能填，0表示不能填
        vector<int> rows(9, init_v), lines(9, init_v);
        vector<vector<int> > grid(3, vector<int>(3, init_v));
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if (board[i][j] == '.')
                    continue;
                int x = i/3, y = j/3;
                int v =board[i][j] - '0';
                if (!(rows[i] >> v & 1 && lines[j] >> v & 1 && grid[x][y] >> v & 1))
                return false;
                rows[i] ^= 1 << v;
                lines[j] ^= 1 << v;
                grid[x][y] ^= 1 << v;
            }
        }
        return true;
    }
};