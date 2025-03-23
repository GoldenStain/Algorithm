#include <stdio.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#define For(i, j, n) for (int i = j; i <= n; ++i)
#ifdef DEBUG
#define DEBUG_LOG(fmt, ...)                  \
    do {                                     \
        fprintf(stderr, fmt, ##__VA_ARGS__); \
    } while (0);
#else
#define DEBUG_LOG(fmt, ...) \
    do {                    \
    } while (0);
#endif

template <typename T>
inline T read() {
    T x = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

using std::queue;
using std::shared_ptr;
using std::string;
using std::vector;

class Solution {
   public:
    int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
    int m, n;
    bool exist(vector<vector<char>> &board, string word) {
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
    bool dfs(vector<vector<char>> &board, int sx, int sy, int cnt,
             string &target, vector<vector<bool>> &vis) {
        if (cnt == target.size() - 1) {
            return board[sx][sy] == target[cnt];
        }
        if (board[sx][sy] != target[cnt]) {
            return false;
        }
        vis[sx][sy] = true;
        for (int i = 0; i < 4; i++) {
            int nx = sx + dx[i], ny = sy + dy[i];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || vis[nx][ny]) continue;
            bool flag = dfs(board, nx, ny, cnt + 1, target, vis);
            if (flag) {
                vis[sx][sy]=false;
                return true;
            }
        }
        vis[sx][sy] = false;
        return false;
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
