#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;
int n, w[N];
ll ans;
int h[N], ne[N << 1], e[N << 1], cnt;

ll dfs(int u, int fa)
{
    ll res = w[u];
    for(int i = h[u]; i; i = ne[i])
    {
        int j = e[i];
        if(j == fa)
            continue;
        res += max(dfs(j, u), 0ll);
    }
    ans = max(ans, res);
    return res;
}

void add(int a, int b)
{
    e[++cnt] = b;
    ne[cnt] = h[a];
    h[a] = cnt;
}

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    for(int i = 1; i < n; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);add(b, a);
    }
    dfs(1, 0);
    printf("%lld\n", ans);
    return 0;
}