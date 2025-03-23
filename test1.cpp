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

template <typename T, int N>
struct MultiVector {
    using type = std::vector<typename MultiVector<T, N-1>::type>;
};

template <typename T>
struct MultiVector<T, 0> {
    using type = T;
};

int main()
{
    MultiVector<int, 2>::type a;
    a.resize(5);
    a[0] = {1};
    return 0;
}
