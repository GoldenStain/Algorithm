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
        queue<TreeNode *> q;
        vector<double> ans;
        q.push(root);
        while (q.size()) {
            TreeNode *head = q.front();
            int n = q.size();
            ans.push_back(0.f);
            if (head->left) q.push(head->left);
            if (head->right) q.push(head->right);
            for (int i = 1; i <= n; i++) {
                head = q.front();
                q.pop();
                ans.back() += head->val;
                if (head->left) q.push(head->left);
                if (head->right) q.push(head->right);
            }
            ans.back() /= n;
        }
        return ans;
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
