#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

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
    std::vector<int> row, col, diag1, diag2;
    int ans = 0;
    int totalNQueens(int n) {
        row.resize(n);
        col.resize(n);
        diag1.resize(n);
        diag2.resize(n);
        dfs(0, 0, n);
    }
    void dfs(int rn, int cnt, int n) {
        if (rn == n) {
            return;
        }
        if (cnt == n) {
            ans++;
            return;
        }
        // 枚举放在哪一列
    }
};

int main() { return 0; }
