#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <limits>

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

int get_length(long long num) {
    double log_val = std::log2(static_cast<double>(num));
    int length = static_cast<int>(std::floor(log_val));
    return length;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    long long l, r;
    std::cin >> l >> r;
    if (l == r) {
        std::cout << "0\n";
        return 0;
    }
    long long p = (1ll << 62);
    while(p&&(l&p)==(r&p))
        p>>=1;
    p = (p<<1)-1;
    std::cout << p << std::endl;
    return 0;
}
