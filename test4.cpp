#include <stdio.h>
#include <unordered_map>
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

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        std::unordered_map<int, int> depth;
        std::unordered_map<int, TreeNode*> fa;
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            dfs(root, 1, nullptr);
            if (depth[p->val] < depth[q->val])
                std::swap(p, q);
            while(depth[p->val] > depth[q->val])
                p = fa[p->val];
            if (p == q)
                return q;
            while(fa[p->val] != fa[q->val])
                p = fa[p->val], q = fa[q->val];
            return fa[p->val];
        }
        void dfs(TreeNode* root, int d, TreeNode* f) {
            depth[root->val] = d;
            fa[root->val] = f;
            dfs(root->left, d + 1, root);
            dfs(root->right, d + 1, root);
        }
    };

int main() { return 0; }
