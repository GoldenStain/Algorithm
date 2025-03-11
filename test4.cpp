#include <stdio.h>

#include <algorithm>
#include <cmath>
#include <iostream>
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

class Solution {
   public:
    std::vector<bool> col, diag1, diag2, row;
    int ans = 0;
    int totalNQueens(int n) {
        col.assign(n + 1, false);
        diag1.assign(2 * n, false);
        diag2.assign(2 * n, false);
        row.assign(n + 1, false);
        dfs(0, 0, n, 0);
        return ans;
    }
    void dfs(int x, int y, int n, int cnt) {
        if (cnt == n) {
            ans++;
            return;
        }
        if (y == n) dfs(x + 1, 0, n, cnt);
        if (x == n) {
            return;
        }
        // 不放
        dfs(x, y + 1, n, cnt);
        // 放
        if (!row[x] && !col[y] && !diag1[x + y] && !diag2[x - y + n]) {
            row[x] = col[y] = diag1[x + y] = diag2[x - y + n] = true;
            dfs(x, y + 1, n, cnt + 1);
            row[x] = col[y] = diag1[x + y] = diag2[x - y + n] = false;
        }
    }
};

int main() { return 0; }
