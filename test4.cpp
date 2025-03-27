#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <deque>
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
    using VecInt = vector<int>;
   public:
    int findLength(vector<int> &nums1, vector<int> &nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        int ans = 0;
        // 移动nums1
        for (int i = 0; i < n1; i++) {
            ans = std::max(ans, getAns(nums1, i, nums2, 0));
        }
        // 移动nums2
        for (int i = 0; i < n2; i++) {
            ans = std::max(ans, getAns(nums1, 0, nums2, i));
        }
        return ans;
    }
    int getAns(VecInt& a, int oa, VecInt& b, int ob) {
        int len = std::min(a.size() - oa, b.size() - ob), res = 0;
        // 需要两个变量来配合统计，如果只用一个变量，那么后面的更小重复字串可能会覆盖前面更长的重复字串，导致我们丢失正确答案。
        int now_len = 0;
        for (int i = 0; i < len; i++) {
            char ca = a[oa + i], cb = b[ob + i];
            if (ca == cb)
                now_len++;
            else {
                res = std::max(res, now_len);
                now_len = 0;
            }
        }
        return res;
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
