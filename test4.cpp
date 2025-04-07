#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <unordered_set>
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
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

using std::queue;
using std::shared_ptr;
using std::string;
using std::vector;

class Solution {
   public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size(), m = obstacleGrid[0].size();
        vector<vector<int>> f(n, vector<int>(m, 0));
        for (int i = 0; i < m; i++) {
            if (obstacleGrid[0][i] == 1)
                f[0][i] = 0;
            else {
                f[0][i] = i == 0 ? 1 : f[0][i - 1];
            }
        }
        for (int i = 0; i < n; i++) {
            if (obstacleGrid[i][0])
                f[i][0] = 0;
            else {
                f[i][0] = i == 0 ? 1 : f[i - 1][0];
            }
        }
        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++)
                if (obstacleGrid[i][j])
                    f[i][j] = 0;
                else
                    f[i][j] = f[i - 1][j] + f[i][j - 1];
        return f[n - 1][m - 1];
    }
};
int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
