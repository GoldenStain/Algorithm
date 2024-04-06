#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 1e6 + 5, mod = 998244353;

typedef long long LL;

int n, deg[N], m;
LL ans;

int f(int a, int b)
{
    return (a ^ b) * (a | b) * (a & b);
}

int main()
{
    scanf("%d%d", &n, &m);
    int a, b;
    for(int i = 1;i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        deg[a]++;
        deg[b]++;
    }
    for(int i = 1; i <= n; i++)
        for(int j = i; j <= n; j++)
            ans = (ans + f(deg[i], deg[j])) % mod;
    printf("%lld\n", ans);
    return 0;
}