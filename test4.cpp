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
    typedef unsigned long long ULL;
    static constexpr ULL base = 113;

   public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        vector<ULL> hash1(n1, 0), hash2(n2, 0);
        initHash(nums1, hash1);
        initHash(nums2, hash2);
        // 一开始左边界设置错了，把l设置为1；要注意最坏情况应该是没有公共元素，所以l应该设置为0.
        int l = 0, r = std::min(n1, n2);
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (check(nums1, hash1, nums2, hash2, mid)) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        return l;
    }
    void initHash(vector<int>& n, vector<ULL>& hash) {
        hash[0] = (ULL)n[0];
        for (int i = 1; i < n.size(); i++) {
            hash[i] = hash[i - 1] * base + (ULL)n[i];
        }
    }

    ULL qPow(ULL base, int len) {
        ULL res = 1;
        while (len) {
            if (len & 1) {
                res *= base;
            }
            base *= base;
            len >>= 1;
        }
        return res;
    }

    ULL query(vector<ULL>& hash, int l, int r) {
        if (l == 0) {
            return hash[r];
        }
        return hash[r] - hash[l - 1] * qPow(base, r - l + 1);
    }

    bool check(vector<int>& nums1, vector<ULL>& hash1, vector<int>& nums2,
               vector<ULL>& hash2, int len) {
        std::unordered_set<ULL> in_nums1, in_nums2;
        for (int i = 0; i + len <= nums1.size(); i++) {
            in_nums1.insert(query(hash1, i, i + len - 1));
        }
        for (int i = 0; i + len <= nums2.size(); i++) {
            ULL query_res = query(hash2, i, i + len - 1);
            if (in_nums1.find(query_res) != in_nums1.end()) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
