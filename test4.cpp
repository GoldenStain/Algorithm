#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <limits>
#include <cstring>
#include <string.h>

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

long long l, r;

long long dp[64][2][2][2][2];

long long vl[64], vr[64];

int cntl, cntr;

void pre_fill(long long target, long long* v, int& cnt) {
    if (!target) {
        v[++cnt] = 0;
        return;
    }
    while(target) {
        v[++cnt] = target & 1;
        target >>= 1;
    }
}

// dp[pos][][][][] 表示从pos位填到第一位，最值是多少
// limit1表示贴合下界，limit2表示贴合上界
long long get_dp(int pos, bool limitl1, bool limitr1, bool limitl2, bool limitr2) {
    if (pos == 0) {
        return 0ll;
    }
    long long ans = 0ll;
    long long &d = dp[pos][limitl1][limitr1][limitl2][limitr2];
    // 这里把limit也放进了状态表示当中，所以只要已经算出来了，就能直接返回。
    if (d != -1) {
        return d;
    }
    // 异或有两个操作数，我们分别选取
    // 两个数字都要满足：l<=x<=r
    for (long long u = (limitl1?vl[pos]:0); u <= (limitr1?vr[pos]:1); u++)
        for (long long v = (limitl2?vl[pos]:0); v <= (limitr2?vr[pos]:1); v++)
            ans = std::max(ans, ((u ^ v) << (pos - 1)) + get_dp(pos - 1, limitl1&(u == vl[pos]), limitr1&(u==vr[pos]), limitl2&(v==vl[pos]), limitr2&(v==vr[pos])));
    d = ans;
    return ans;
}

long long work(long long l, long long r) {
    if (l == r) {
        return 0ll;
    }
    memset(dp, -1, sizeof(dp));
    pre_fill(l, vl, cntl);
    pre_fill(r, vr, cntr);
    return get_dp(std::max(cntl, cntr), 1, 1, 1, 1);// 一开始什么都没填，相当于所有限制都要满足，即第一次填的数字不能随便选
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> l >> r;
    std::cout << work(l, r);
    return 0;
}
