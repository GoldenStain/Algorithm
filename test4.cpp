#include <stdio.h>
#include <string.h>

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
    int minCut(string s) {
        int n = s.size();
        if (n == 1) {
            return 0;
        }
        vector<vector<bool>> g(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++) g[i][i] = true;
        for (int len = 2; len < n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;
                if (i + 1 > j - 1)
                    g[i][j] = (s[i] == s[j]);
                else
                    g[i][j] = g[i + 1][j - 1] & (s[i] == s[j]);
            }
        }
        vector<int> f(n, 0);
        for (int i = 0; i < n; i++) {
            if (g[0][i]) {
                f[i] = 0;
                continue;
            }
            for (int j = 0; j < i; j++) {
                if (g[j][i - 1]) f[i] = std::min(f[i], f[j] + 1);
            }
        }
        return f[n - 1];
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
