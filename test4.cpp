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
    int countNodes(TreeNode *root) {
        if (!root)
            return 0;
        int depth = cnt(root) - 1; // 从0开始
        int l = (1 << depth), r = (1 << (depth + 1)) - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (check(mid, root)) {
                l = mid;
            }
            else 
                r = mid - 1;
        }
        return l;
    }
    int cnt(TreeNode *root) {
        if (!root) 
            return 0;
        return 1 + cnt(root->left);
    }
    bool check(int x, TreeNode* root) {
        TreeNode* cur = root;
        int bit = 2;
        while (x) {
            if (!cur)
                return false;
            int now_bit = (x >> bit) & 1;
            if (now_bit)
                cur = cur->right;
            else
                cur = cur->left;
        }
        return cur != nullptr;
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
