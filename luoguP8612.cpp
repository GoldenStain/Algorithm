#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
using namespace std;

const int N = 55, mod = 1e9 + 7;

int f[N][N][15][15]; // 横坐标 纵坐标 最大值 数量
bool vis[N][N][15][15];
int n, m, k, a[N][N];

int dfs(int x, int y, int s, int top) // 当前在x,y  当前拿了s个， 当前的最大值是top
{
    int &res = f[x][y][s][top];
    if (vis[x][y][s][top])
        return res;
    vis[x][y][s][top] = 1;
    if (x == n && y == m)
    {
        if (s == k)
            f[x][y][s][top] = 1;
        return f[x][y][s][top];
    }
    if (x + 1 <= n)
    {
        res = (long long)(res + dfs(x + 1, y, s, top)) % mod;
        if (a[x + 1][y] > top)
            res = (long long)(res + dfs(x + 1, y, s + 1, a[x + 1][y])) % mod;
    }
    if (y + 1 <= m)
    {
        res = (long long)(res + dfs(x, y + 1, s, top)) % mod;
        if (a[x][y + 1] > top)
            res = (long long)(res + dfs(x, y + 1, s + 1, a[x][y + 1])) % mod;
    }
    return res;
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &a[i][j]);
        }
    printf("%d\n", (dfs(1, 1, 0, -1) + dfs(1, 1, 1, a[1][1])) % mod);
    system("pause");
    return 0;
}