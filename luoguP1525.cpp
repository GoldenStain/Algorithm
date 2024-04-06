#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

const int N = 20005, M = 100005;

int fa[N], d[N];
int n, m;
struct _edges
{
    int a, b, w;
    bool operator<(const _edges &t) const
    {
        return w > t.w;
    }
} Edge[M];

void init(int n)
{
    for (int i = 1; i <= n; i++)
        fa[i] = i;
}

int find(int a)
{
    if (a == fa[a])
        return a;
    int old_fa = fa[a];
    fa[a] = find(old_fa);
    d[a] = (d[a] + d[old_fa]) % 2;
    return fa[a];
}

int solve()
{
    for (int i = 1; i <= m + 1; i++)
    {
        int a = Edge[i].a, b = Edge[i].b;
        int x = find(a), y = find(b);
        if (x != y)
        {
            d[x] = (d[b] - d[a] + 3) % 2;
            fa[x] = y;
           // printf("D %d %d %d %d %d\n", a, b, x, y, d[x])
        }
        else
        {
            if((d[a] - d[b] + 2) % 2 == 0)
                return Edge[i].w;
        }
    }
    return 0;
}

int main()
{
    scanf("%d%d", &n, &m);
    init(n);
    int a, b, w;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &w);
        Edge[i] = {a, b, w};
    }
    Edge[m + 1] = {0, 0, 0};
    sort(Edge + 1, Edge + m + 1);
    cout << solve();
    return 0;
}
