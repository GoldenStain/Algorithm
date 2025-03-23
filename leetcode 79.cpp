// wrong solution
class Solution {
   public:
    int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
    int m, n;
    bool exist(vector<vector<char>>& board, string word) {
        int len = word.size();
        m = board.size();
        n = board[0].size();
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                std::string tmp("");
                if (dfs(board, i, j, len, tmp, word, vis)) return true;
            }
        }
        return false;
    }
    bool dfs(vector<vector<char>>& board, int sx, int sy, int steps, string now,
             string& target, vector<vector<bool>>& vis) {
        // 这种做法只有走到目标单词的范围之外，比如我们要找"SSE"，我们找到"SSE"之后，我们在下一个格子才进行判断
        // 如果棋盘上空间有限，我们就没有机会进行这个判断，就出错了。
        // 比如棋盘上只有一个'a'的时候。
        if (!steps) {
            if (now == target) return true;
            return false;
        }
        vis[sx][sy] = true;
        for (int i = 0; i < 4; i++) {
            int nx = sx + dx[i], ny = sy + dy[i];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || vis[nx][ny]) continue;
            if (dfs(board, nx, ny, steps - 1, now + board[sx][sy], target, vis))
                return true;
        }
        vis[sx][sy] = false;
        return false;
    }
};

// slow solution
class Solution {
   public:
    int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
    int m, n;
    bool exist(vector<vector<char>>& board, string word) {
        int len = word.size();
        m = board.size();
        n = board[0].size();
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                std::string tmp;
                tmp.append(1, board[i][j]);
                vis[i][j] = true;
                if (dfs(board, i, j, len - 1, tmp, word, vis)) return true;
                // dfs函数中没有人可以回溯vis[i][j]，需要我们手动回溯。
                vis[i][j] = false;
            }
        }
        return false;
    }
    bool dfs(vector<vector<char>>& board, int sx, int sy, int steps, string now,
             string& target, vector<vector<bool>>& vis) {
        if (!steps) {
            if (now == target) return true;
            return false;
        }
        for (int i = 0; i < 4; i++) {
            int nx = sx + dx[i], ny = sy + dy[i];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || vis[nx][ny]) continue;
            vis[nx][ny] = true;
            if (dfs(board, nx, ny, steps - 1, now + board[nx][ny], target, vis))
                return true;
            vis[nx][ny] = false;
        }
        return false;
    }
};

// fast solution
class Solution {
   public:
    int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
    int m, n;
    bool exist(vector<vector<char>>& board, string word) {
        int len = word.size();
        m = board.size();
        n = board[0].size();
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(board, i, j, 0, word, vis)) return true;
            }
        }
        return false;
    }
    bool dfs(vector<vector<char>>& board, int sx, int sy, int cnt,
             string& target, vector<vector<bool>>& vis) {
        // 注意不能把vis[sx][sy] = true;
        // 写在这里，否则就会导致这个格子没有被回溯，从而影响正确性。
        // 如果我走到了一个格子，然后又发现这里行不通，相当于我先把vis置为true，然后又立刻回溯，相当于啥也没做
        // 所以vis[sx][sy] = true直接写到这两个return判定的后面即可。
        if (cnt == target.size() - 1) {
            return board[sx][sy] == target[cnt];
        }
        if (board[sx][sy] != target[cnt]) {
            return false;
        }
        vis[sx][sy] = true;
        bool res = false;
        for (int i = 0; i < 4; i++) {
            int nx = sx + dx[i], ny = sy + dy[i];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || vis[nx][ny]) continue;
            bool flag = dfs(board, nx, ny, cnt + 1, target, vis);
            // 这里也可以不用break，而是写成：
            //  if (flag) {
            //     vis[sx][sy]=false;
            //     return true;
            // }
            // 即舍弃了res的使用，只要还能保证回溯正确即可。
            if (flag) {
                res = true;
                break;
            }
        }
        vis[sx][sy] = false;
        return res;
    }
};