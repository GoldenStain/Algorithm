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
    int ans = INT_MIN;

   public:
    int maxPathSum(TreeNode *root) {
        dfs(root);
        return ans;
    }
    int dfs(TreeNode* root) {
        if (!root) {
            return INT_MIN;
        }
        ans = std::max(ans, root->val);// 至少要包含一个节点
        if (!root->left && !root->right) {
            return root->val;
        }
        int l_max = 0, r_max = 0;
        r_max = dfs(root->right);
        l_max = dfs(root->left);
        ans = std::max(ans, r_max);
        ans = std::max(ans, l_max);
        ans = std::max(ans, r_max + root->val + l_max);
        return std::max(l_max, r_max) + root->val;
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
