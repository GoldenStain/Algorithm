#include <stdio.h>

#include <algorithm>
#include <cmath>
#include <iostream>
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

class Solution {
    using string = std::string;

   public:
    bool wordBreak(string s, std::vector<string> dicts) {
        int len = s.size();
        std::vector<int> dp(len+1, false);
        dp[0] = true;
        for (int i = 0; i < len; i++) {
            // 没必要进行转移
            if (!dp[i])
                continue;
            for (int j = 0; j < dicts.size(); j++) {
                int jlen = dicts[j].size();
                // 如果后面的元素个数不足jlen个，substr函数会自己截断。
                string tmp =s.substr(i, jlen);
                if (tmp == dicts[j]) {
                    dp[i + jlen] = true;
                }
            }
        }
        return dp[len];
    }
};

int main() { return 0; }
