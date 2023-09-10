#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
using namespace std;
typedef pair<int, int> PII;

//西，北，东，南

const int N = 55;

int m, n, g[N][N], ans;
bool st[N][N];
PII q[N*N];

int bfs(int sx, int sy)
{
    int cnt = 1;
    int dx[] = {0, -1, 0, 1};
    int dy[] = {-1, 0, 1, 0};
    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    st[sx][sy] = 1;
    while(hh <= tt)
    {
        PII tmp = q[hh++];
        int nx = tmp.first, ny = tmp.second;
        for(int i = 0; i < 4; i++)
        {
            if(!(g[nx][ny] & 1)) continue;
            int ex = nx + dx[i], ey = ny + dy[i];
            if(st[ex][ey]) continue;
            if(ex < 1 || ex > n) continue;
            if(ey < 1 || ey > m) continue;
            st[ex][ey] = true;
            cnt++;
            q[++tt] = {ex, ey};
        }
    }
    return cnt;
}

int main()
{
    cin >> m >> n;
    for(int i = 1; i <= n; i++)
     for(int j = 1; j <= m; j++)
      cin >> g[i][j];
    for(int i = 1; i <= n; i++)
     for(int j = 1; j <= m; j++)
      if(!st[i][j])
       ans = max(ans, bfs(i, j));
    cout << ans; 
    return 0;
}