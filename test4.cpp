#include <stdio.h>

#include <algorithm>
#include <cmath>
#include <iostream>
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

using std::cin, std::cout;
using std::vector;
class Solution {
   public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> stk;
        int ans = 0, n = heights.size();
        vector<int> left(n, -1), right(n, n); // -1和n对应边界情况
        for (int i = 0; i < n; i++) {
            while(stk.size() && heights[i] < heights[stk.back()]) {
                right[stk.back()] = i;
                stk.pop_back();
            }
            if (stk.size()) left[i] = stk.back();
            stk.push_back(i);
        }
        for (int i = 0; i < n; i++)
            ans = std::max(ans, (right[i] - left[i] - 1) * heights[i]);
        return ans;
    }
};

int main() { return 0; }
