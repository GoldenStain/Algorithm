#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>

#define For(i, j, n) for(int i = j ; i <= n ; ++i)
#ifdef DEBUG
#define DEBUG_LOG(fmt, ...)                  \
do {                  \
\
fprintf(stderr, fmt, ##__VA_ARGS__); \
} while (0);
#else
#define DEBUG_LOG(fmt, ...) \
do {                    \
} while (0);
#endif

template <typename T>
inline T read()
{
    T x = 0;
    int f = 1; char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
       x = x * 10 + ch - '0';
       ch = getchar();
    }
    return x * f;
}

void get_ans(std::vector<std::string>& vec, size_t len, std::string& s, std::string &now, int pos) {
    if (pos == len) {
        if (now.size())
            vec.emplace_back(now);
        return;
    }
    for (int i = pos; i < len; i++) {
        // 选择
        now.append(1, s[i]);
        get_ans(vec, len, s, now, i + 1);
        now.pop_back();
        get_ans(vec, len, s, now, i + 1);
    }
}

int main()
{
    std::string s = "abc";
    std::vector<std::string> ans;
    std::string now = "";
    get_ans(ans, s.size(), s, now, 0);
    for (auto i: ans)
        std::cout << i << std::endl;
    return 0;
}
