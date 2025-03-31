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
    std::unordered_set<std::string> S;
    vector<bool> vis;

   public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        S = std::unordered_set<std::string>(wordDict.begin(), wordDict.end());
        std::vector<std::vector<string>> splited_words(s.size() + 1,
                                                       vector<string>{});
        vis = std::vector<bool>(s.size() + 1, false);
        dfs(0, splited_words, s);
        return splited_words[0];
    }
    void dfs(int pos, std::vector<std::vector<string>>& splited_words,
             string& s) {
        if (vis[pos]) return;
        vis[pos] = true;
        if (pos == s.size()) {
            // 需要手动放一个空的字符串，否则不能跟前面的接上
            splited_words[pos] = {""};
            return;
        }
        for (int i = pos + 1; i <= s.size(); i++) {
            // pos ~ i-1 是当前的，i~往后是后面一串的
            string tmp = s.substr(pos, i - pos);
            dfs(i, splited_words, s);
            if (S.count(tmp)) {
                for (auto& si : splited_words[i]) {
                    splited_words[pos].emplace_back(si.empty() ? tmp
                                                               : tmp + " " + si);
                }
            }
        }
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
