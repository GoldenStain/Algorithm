#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
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

const int N = 15;

int a[N][N], m, n; //n行m列
int ans = 999, tar;
bool vis[N][N];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void dfs(int x, int y, int cnt, int sum)
{
    if(cnt >= ans)
        return;
    if(sum > tar)
        return;
    if(sum == tar)
    {
        ans = cnt;
        return;
    }
    vis[x][y] = 1;
    for(int i = 0; i < 4; i++)
    {
        int nx = x + dx[i], ny = y + dy[i];
        if(nx < 1 || nx > n || ny < 1 || ny > m || vis[nx][ny]) continue;
        dfs(nx, ny, cnt + 1, sum + a[x][y]);
    }
    vis[x][y] = 0;
}

int main()
{
    R(m);R(n);
    For(i, 1, n)
        For(j, 1, m)
            R(a[i][j]), tar += a[i][j];
    if(tar & 1)
    {
        puts("0");
        return 0;
    }
    tar >>= 1;
    dfs(1, 1, 0, 0);
    if(ans == 999)
        puts("0");
    else
        printf("%d\n", ans);
    return 0;
}
