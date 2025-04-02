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
    int superEggDrop(int k, int n) {
        vector<vector<int>> f(k + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= n; i++) f[1][i] = i;
        for (int i = 2; i <= k; i++) {
            for (int j = 1; j <= n; j++) {
                f[i][j] = 1 + getF(f, i, j);
            }
        }
        return f[k][n];
    }
    int getF(vector<vector<int>>& f, int k, int x) {
        // 注意这个函数内部的“总楼层”应该是等于我们传入的j，而不是实际的最大楼层n
        // 推公式的时候用的是字母n，结果导致函数参数传递错误，debug了半天。
        int l = 1, r = x;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (f[k - 1][mid - 1] < f[k][x - mid])
                l = mid;
            else
                r = mid - 1;
        }
        int res = std::max(f[k - 1][l - 1], f[k][x - l]);
        if (x - l)  // 这个下标可能会越界，所以要判断一下
        {
            res = std::min(res, std::max(f[k - 1][l], f[k][x - l - 1]));
        }
        return res;
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
