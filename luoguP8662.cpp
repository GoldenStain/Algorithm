#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

const int N = 1005;

int n, ans, block_cnt, dead_cnt;
char g[N][N];
int dx[] = {-1, 1, 0, 0},
    dy[] = {0, 0, -1, 1};
bool vis[N][N];

void dfs(int x, int y)
{
    bool has_ocean = false;
    vis[x][y] = 1;
    block_cnt++;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i], ny = y + dy[i];
        if(nx < 0 || nx >= n || ny < 0 || ny >= n || vis[nx][ny])
            continue;
        if(g[nx][ny] == '.')
            has_ocean = true;
        if(g[nx][ny] == '#')
            dfs(nx, ny);
    }
    if(has_ocean) 
        dead_cnt++;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%s", g[i]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!vis[i][j] && g[i][j] == '#')
            {
                block_cnt = 0;
                dead_cnt = 0;
                dfs(i, j);
                if (block_cnt == dead_cnt)
                    ans++;
            }
    printf("%d\n", ans);
    return 0;
}
