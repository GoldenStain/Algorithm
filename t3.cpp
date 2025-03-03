#include <iostream>
#include <stdio.h>
#include <algorithm>
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

constexpr int N = 1e5 + 5, CAP = 1e6 + 5;

int n;

long long alone_price[CAP], S, alone_cost, total_cost;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n >> S;
    int pi, ci, max_ci = -1;
    for(int i = 0; i < n; i++) {
        std::cin >> pi >> ci;
        long long tmp = (long long)(pi) * ci;
        alone_price[ci] += pi;
        alone_cost += pi;
        total_cost += tmp;
        max_ci = std::max(max_ci, ci);
    }
    long long group_cost = 0;
    for(int i = 1; i <= max_ci; i++) {
        if (alone_cost < S) {
            break;
        }
        group_cost += S;
        total_cost -= alone_cost;
        alone_cost -= alone_price[i];
    }
    std::cout << group_cost + total_cost;
    return 0;
}
