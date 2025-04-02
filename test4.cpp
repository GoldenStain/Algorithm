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
        vector<vector<int>> f(2, vector<int>(n + 1, 0));
        // 要先给idx赋值为1，如果鸡蛋只有1个的话，那这里的idx就作为最终输出了
        int idx = 1;
        for (int i = 1; i <= n; i++)
            f[1][i] = i;
        for (int i = 2; i <= k; i++) {      // 鸡蛋
            int point = 1;
            idx = i & 1;
            f[idx][1] = 1;
            for (int j = 2; j <= n; j++) {  // 层数
                while (point < j && f[idx^1][point - 1] < f[idx][j - point])
                    point++;
                f[idx][j] = std::max(f[idx^1][point - 1], f[idx][j - point]) + 1;
            }
        }
        return f[idx][n];
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
