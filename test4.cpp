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

using std::string;
using std::vector;

class Solution {
   public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string cur;
        dfs(ans, cur, 0, 0, n);
        return ans;
    }
    void dfs(vector<string>& ans, string cur, int left, int right, int n) {
        if (cur.size() == 2 * n) {
            ans.emplace_back(cur);
            return;
        }
        if (left < n) {
            cur.append(1, '(');
            dfs(ans, cur, left + 1, right, n);
            cur.pop_back();
        }
        if (right < left) {
            cur.append(1, ')');
            dfs(ans, cur, left, right + 1, n);
            cur.pop_back();
        }
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
