#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <string.h>
#define R(x) x = read()
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 50005;
typedef long long LL;

int n, a[N];
int Log[N];
int Max[N][17], Min[N][17]; //2^16 = 65536

void init()
{
    memset(Min, 0x3f, sizeof(Min));
    Log[0] = -1;
    for(int i = 1; i <= n; i++)
        Log[i] = Log[i>>1] + 1, Min[i][0] = Max[i][0] = a[i];
    for(int j = 1; j <= 16; j++)
    {   
        for(int i = 1; i + (1 << j - 1) <= n; i++)
            Max[i][j] = max(Max[i][j - 1], Max[i + (1 << j - 1)][j -1]),
            Min[i][j] = min(Min[i][j - 1], Min[i + (1 << j - 1)][j - 1]);
    }
}

int query(int l, int r, int t)
{
    int len = r - l + 1;
    if(t)
        return max(Max[l][Log[len]], Max[r - (1 << Log[len]) + 1][Log[len]]);
    else
        return min(Min[l][Log[len]], Min[r - (1 << Log[len]) + 1][Log[len]]);
}

int main()
{
    R(n);
    For(i, 1, n)
        R(a[i]);
    init();
    LL ans = 0ll;
    for(int len = 1; len <= n; len++)
        for(int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            ans += (query(i, j, 1) - query(i, j, 0) == len - 1);
        }
    printf("%lld\n", ans);
    return 0;
}
