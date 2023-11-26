#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5, M = N << 1;

int n, cnt, h[N], e[M], w[M], ne[M];

inline void add(int a, int b, int c)
{
    e[++cnt] = b;
    w[cnt] = c;
    ne[cnt] = h[a];
    h[a] = cnt;
}
int t, maxd, maxu;

void dfs(int u, int fa,int dis)
{
    if(dis > maxd)
    {
        maxd = dis;
        maxu = u;
    }
    for(int i = h[u]; i; i = ne[i])
    {
        int j = e[i];
        if(j == fa) continue;
        dfs(j, u, dis + w[i]);
    }
}

int main()
{
    scanf("%d", &n);
    for(int i = 1; i < n; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
    dfs(1, 0, 0);
    dfs(maxu, 0, 0);
    ll ans = (ll) maxd * 10L +(ll) maxd * (maxd + 1) / 2;
    printf("%lld\n", ans);
    system("pause");
    return 0;
}