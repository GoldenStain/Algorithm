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
    int minimumTotal(vector<vector<int>> &triangle) {
        int n = triangle.size();
        vector<vector<int>> f(2, vector<int>(n, 100000000));
        int idx;
        // 设置边界条件
        for (int i = 0; i < n; i++) f[(n - 1) & 1][i] = triangle[n - 1][i];
        for (int i = n - 2; i >= 0; i--) {
            idx = i & 1;
            for (int j = 0; j <= i; j++) {
                f[idx][j] = std::min(f[idx ^ 1][j] + triangle[i][j], f[idx ^ 1][j + 1] + triangle[i][j]);
            }
        }
        return f[idx][0];
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
