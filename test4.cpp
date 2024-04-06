#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#define R(x) x = read()
using namespace std;

const int N = 32;

int n, m, a[N], ans = 0x3f3f3f3f, mid;
unordered_map<int, int> Map;

inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}

inline void dfs1(int now, int p, int w)
{
    if (p > ans || w > m || (Map.count(w) && Map[w] < p))
        return;
    if (w == m)
    {
        ans = min(ans, p);
        return;
    }
    if (now == mid + 1)
    {
        if (w < m)
        {
            if (Map.count(w))
                Map[w] = min(Map[w], p);
            else
                Map[w] = p;
        }
        return;
    }
    dfs1(now + 1, p, w);
    dfs1(now + 1, p + 1, w + a[now]);
    dfs1(now + 1, p, w + (a[now] << 1));
}

inline void dfs2(int now, int p, int w)
{
    if (p > ans || w > m)
        return;
    if (w == m)
    {
        ans = min(ans, p);
        return;
    }
    if (now == n + 1)
    {
        if(w < m && Map.count(m - w)) ans = min(ans, Map[m - w] + p);
        return;
    }
    dfs2(now + 1, p, w);
    dfs2(now + 1, p + 1, w + a[now]);
    dfs2(now + 1, p, w + (a[now] << 1));
}

bool cmp(int a, int b)
{
    return a>b;
}

int main()
{
    scanf("%d%d", &n, &m);
    mid = n >> 1;
    m <<= 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    //sort(a + 1, a + n + 1, cmp);
    dfs1(1, 0, 0); // 现在是第几个，已经劈了几个，总重是多少
    dfs2(mid + 1, 0, 0);
    if(ans != 0x3f3f3f3f) printf("%d\n", ans);
    else printf("-1\n");
    system("pause");
    return 0;
}