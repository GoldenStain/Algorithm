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

using std::queue;
using std::shared_ptr;
using std::string;
using std::vector;

class Solution {
   public:
    int minMoves(vector<int>& nums, int k) {
        int n = nums.size();
        std::vector<int> g, preSum;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 1) {
                g.emplace_back(i - g.size());
                if (preSum.empty()) {
                    preSum.emplace_back(g.back());
                } else {
                    preSum.emplace_back(preSum.back() + g.back());
                }
            }
        }
        n = g.size();
        int ans = -1;
        for (int i = 0; i + k <= n; i++) {
            int now, _end = i + k - 1, mid = (i + _end) >> 1;
            if (k & 1) {
                now = getPreSum(preSum, mid + 1, _end) -
                      getPreSum(preSum, i, mid - 1);
            } else
                now = getPreSum(preSum, mid + 1, _end) -
                      getPreSum(preSum, i, mid - 1) - g[mid];
            ans = inline_min(ans, now);
        }
        return ans;
    }
    inline int getPreSum(vector<int>& preSum, int l, int r) {
        if (l > r) return 0;
        if (l == 0) {
            return preSum[r];
        }
        return preSum[r] - preSum[l - 1];
    }
    inline int inline_min(int a, int b) {
        if (a < 0)
            return b;
        else
            return std::min(a, b);
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
