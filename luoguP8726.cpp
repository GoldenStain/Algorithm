#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define R(x) x = read()
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

inline int read()
{
    int x = 0, f = 1; char ch = getchar();
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

typedef long long LL;

const int N = 5005;

int n, t[N], f[N];
LL dp[N];

int main()
{
    R(n);
    For(i, 1, n)
        R(t[i]);
    For(i, 1, n)
        R(f[i]);
    dp[1] = 0;
    for(int i = 2; i <= n; i++)
        for(int j = 1; j < i; j++)
            dp[i] = max(dp[i], dp[j]/2 - f[j] + t[j]*t[i]);
    LL ans = 0;
    for(int i = 1; i <= n; i++)
        ans = max(ans, dp[i]);
    cout << ans << endl;
    return 0;
}
