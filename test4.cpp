#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

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

int main()
{
    std::vector<std::vector<int>> dp(5, std::vector<int>(2, 0));
    std::cout << dp[0][0] << " " << dp[0][1] << std::endl;
    return 0;
}
