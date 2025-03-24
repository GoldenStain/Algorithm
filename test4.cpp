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
    vector<double> averageOfLevels(TreeNode *root) {
        if (!root) {
            return vector<double>{};
        }
        vector<double> ans;
        vector<int> size;
        dfs(root, 1, ans, size);
        for (int i = 0; i < ans.size(); i++)
            ans[i]/=(double)size[i];
        return ans;
    }
    void dfs(TreeNode* root, int depth, vector<double>& ans, vector<int>& size) {
        if (!root) {
            return;
        }
        if (ans.size() < depth) {
            ans.emplace_back((double)root->val);
            size.emplace_back(1);
        }
        else {
            // 这里的下标从0开始，所以要减去一
            ans[depth-1] += root->val;
            size[depth-1]++;
        }
        dfs(root->left, depth+1, ans, size);
        dfs(root->right, depth+1, ans, size);
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
