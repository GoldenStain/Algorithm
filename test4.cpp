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
    int lengthOfLIS(vector<int> &nums) {
        if (nums.size() == 1) {
            return 1;
        }
        int n = nums.size();
        vector<int> ups;
        ups.push_back(nums[0]);
        for (int i = 1; i < n; i++) {
            if (nums[i] > ups.back()) {
                ups.emplace_back(nums[i]);
            } else {
                auto pos = std::lower_bound(ups.begin(), ups.end(), nums[i]);
                std::cout << pos - ups.begin();
                *pos = nums[i];
            }
        }
        return ups.size();
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
