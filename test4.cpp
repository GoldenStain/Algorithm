#include <stdio.h>
#include <memory>
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

using std::string;
using std::vector;
using std::shared_ptr;

class Solution {
    vector<shared_ptr<vector<string>>> dp;
   public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string cur;
        dp.assign(n, nullptr);
        return *dfs(n);
    }
    
    shared_ptr<vector<string>> dfs(int n) {
        if (dp[n]) 
            return dp[n];
        auto res = std::make_shared<vector<string>>();
        if (n == 0) {
            res->emplace_back("");
            dp[0] = res;
            return res;
        }
        for (int i = 0; i < n; i++) {
            auto left = dfs(i), right = dfs(n - i - 1);
            for (auto &li: *left) { // 因为是指针，要记得解引用
                for (auto &ri: *right) {
                    res->emplace_back("(" + li + ")" + ri);
                }
            }
        }
        dp[n] = res;
        return res;
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
